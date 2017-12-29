#include "../include/nBody.h"
#define DAMPENING 512.f
nBody::nBody()
{
    //ctor
}

nBody::~nBody()
{
    //dtor
    delete[] particles;
    delete[] quadNodes;
    delete Qtree;
}

nBody::nBody(std::string filename)
{
    /*
    file format:
    line 0:numberOfParticles widthOfField heightOfField
    line 1:xPosition yPosition xVelocity yVelocity xAcceleration yAcceleration mass
    .
    .repeat numberOfParticles times
    .
    */
    std::ifstream particleFile(filename);
    if(!particleFile.is_open()){
        printf("Error opening %s.\n", filename.c_str());
    }
    else{
        particleFile >> numParticles >> fieldWidth >> fieldHeight;
        this->particles = new particle[numParticles];
        this->quadNodes = new quadNode[numParticles];
        int i = 0;
        while(!particleFile.eof()){
    //        particles[i] = new particle;
            particleFile >> particles[i].xPos;
            particleFile >> particles[i].yPos;

            particleFile >> particles[i].xVelocity;
            particleFile >> particles[i].yVelocity;

            particleFile >> particles[i].xAccel;
            particleFile >> particles[i].yAccel;

            particleFile >> particles[i].mass;

            quadNodes[i].particleNode = &particles[i];
            i++;
        }
//        Qtree = quadtree<quadNode>(0,0,fieldWidth, fieldHeight);
        Qtree = nullptr;
        particleFile.close();
        this->updateQuadTree();
    }
}

int nBody::updateQuadTree()
{
    if(Qtree != nullptr ){
        delete Qtree;
    }
    Qtree = new quadtree<quadNode>(0,0,fieldWidth, fieldHeight);
    for(int i = 0; i < this->numParticles; i++){
        if(quadNodes[i].particleNode->xPos > 0 &&
           quadNodes[i].particleNode->xPos < fieldWidth &&
           quadNodes[i].particleNode->yPos > 0 &&
           quadNodes[i].particleNode->yPos < fieldHeight){
            if(Qtree->insertElement(&quadNodes[i], quadNodes[i].particleNode->xPos,
                                quadNodes[i].particleNode->yPos) == -1){
                printf("Problem encountered attempting to insert particle into quadtree.\n");
                return -1;
            }
       }else{
//            printf("Unable to insert point (%d, %d), not in bounds.\n", quadNodes[i].particleNode->xPos,
//                   quadNodes[i].particleNode->yPos);
       }
    }
    return 0;
}

int nBody::updateNetForce()
{
    int retVal = 0;
    for(int i = 0; i < this->numParticles; i++){
        retVal = this->calculateNetForce(&(this->particles[i]), (this->Qtree));
        if(retVal == -1){
            printf("Error calculating net force.\n");
            return retVal;
        }
    }
    return retVal;
}

int nBody::simulate(double timestep)
{
    particle* particles = this->particles;
    for(int i = 0; i < this->getParticleNum(); i++){
        this->updateAcceleration(&particles[i]);
        this->updateVelocity(&particles[i], timestep);
        this->updatePosition(&particles[i], timestep);
    }
    return 0;
}

int nBody::updateAcceleration(particle* P)
{
    P->xAccel = P->forceX / P->mass;
    P->yAccel = P->forceY / P->mass;
    return 0;
}

int nBody::updateVelocity(particle* P, double timestep)
{
    P->xVelocity += (P->xAccel * timestep);
    P->yVelocity += (P->yAccel * timestep);
    return 0;
}

int nBody::updatePosition(particle* P, double timestep)
{
    P->xPos += (P->xVelocity * timestep);
    P->yPos += (P->yVelocity * timestep);
    return 0;
}

int nBody::calculateNetForce(particle* P, quadtree<quadNode>* Q)
{

    if(Q->getValue() == nullptr){
        return 0;
    }

    double distance, Xdist, Ydist, gravNetForce;
    if(Q->isExternalNode()){
        if(Q->getValue()->particleNode->xPos == P->xPos &&
           Q->getValue()->particleNode->yPos == P->yPos){
//            printf("Can't calculate force acting on same object.\n");
            return 0;
        }
        distance = 0x5f3759df - ((int)(std::sqrt(std::pow(P->xPos - Q->getValue()->centerOfMassX, 2) +
                     std::pow(P->yPos - Q->getValue()->centerOfMassY,2)) + DAMPENING) >> 1);
//        printf("Distance value is %f\n", distance);
        particle* qParticle = Q->getValue()->particleNode;
        Xdist = (P->xPos - qParticle->xPos);
        Ydist = (P->yPos - qParticle->yPos);
        gravNetForce = -1*(GRAV_CONST * P->mass * qParticle->mass) / distance;
//        printf("Gravitational net force is %.18f given pmass %.9f and qmass %.9f with Gforce %.9f.\n",
//               gravNetForce, P->mass, qParticle->mass, GRAV_CONST);
        P->forceX += (gravNetForce * Xdist);
        P->forceY += (gravNetForce * Ydist);
//        printf("Net Force: (%.20f, %.20f)\n", P->forceX, P->forceY);
        return 0;
    }

        distance = 0x5f3759df - ((int)(std::sqrt(std::pow(P->xPos - Q->getValue()->centerOfMassX, 2) +
                     std::pow(P->yPos - Q->getValue()->centerOfMassY,2)) + DAMPENING) >> 1);
    if(((double)Q->getsX())/distance > this->calculationThreshold){
        for(int i = 0; i < 4; i++){
            this->calculateNetForce(P, Q->getQuads()[i]);
        }
        return 0;
    }else{
        quadNode* node = Q->getValue();
        Xdist = (P->xPos - node->centerOfMassX);
        Ydist = (P->yPos - node->centerOfMassY);

        gravNetForce = -1*(GRAV_CONST * P->mass * node->massOfChildren) / distance;

        P->forceX += (gravNetForce * Xdist);
        P->forceY += (gravNetForce * Ydist);

        return 0;
    }

    printf("Unable to calculate net force.\n");
    return -1;
}

double calculateMassOfChildren(quadtree<quadNode>* Q)
{
//    printf("At %p\n", Q);
    if(!Q->isExternalNode()){
//        printf("getting child mass\n");
        Q->getValue()->massOfChildren = 0.f;
        for(int i = 0; i < 4; i++){
            Q->getValue()->massOfChildren += calculateMassOfChildren(Q->getQuads()[i]);
        }
        return Q->getValue()->massOfChildren;

    }else{
        if(Q->getValue() != nullptr && Q->getValue()->particleNode != nullptr){
//            printf("Returning %f\n", Q->getValue()->particleNode->mass);
            return Q->getValue()->particleNode->mass;
        }
        else{
            return 0.f;
        }
    }
}

double calculateCenterOfMassX(quadtree<quadNode>* Q)
{
    if(Q->getValue() == nullptr){return 0.f;}
    Q->getValue()->centerOfMassX = 0.f;
    if(!Q->isExternalNode()){
        for(int i = 0; i < 4; i++){
            quadtree<quadNode>* qNode = Q->getQuads()[i];
            if(qNode != nullptr){
                if(!qNode->isExternalNode()){
                    Q->getValue()->centerOfMassX += (qNode->getValue()->massOfChildren * calculateCenterOfMassX(qNode));
                }
                else{
                    if(qNode->getValue() != nullptr){
                        Q->getValue()->centerOfMassX += qNode->getValue()->particleNode->mass *
                                                        qNode->getValue()->particleNode->xPos;
                    }
                }
            }else{
                return 0.f;
            }
        }
        Q->getValue()->centerOfMassX = Q->getValue()->centerOfMassX/Q->getValue()->massOfChildren;
        return Q->getValue()->centerOfMassX;
    }
    return 0.f;
}

double calculateCenterOfMassY(quadtree<quadNode>* Q)
{
    if(Q->getValue() == nullptr){return 0.f;}
    Q->getValue()->centerOfMassY = 0.f;
    if(!Q->isExternalNode()){
        for(int i = 0; i < 4; i++){
            quadtree<quadNode>* qNode = Q->getQuads()[i];
            if(qNode != nullptr){
                if(!qNode->isExternalNode()){
                    Q->getValue()->centerOfMassY += (qNode->getValue()->massOfChildren * calculateCenterOfMassY(qNode));
                }
                else{
                    if(qNode->getValue() != nullptr){
                        Q->getValue()->centerOfMassY += qNode->getValue()->particleNode->mass *
                                                        qNode->getValue()->particleNode->yPos;
                    }
                }
            }else{
                return 0.f;
            }
        }
        Q->getValue()->centerOfMassY = Q->getValue()->centerOfMassY/Q->getValue()->massOfChildren;
        return Q->getValue()->centerOfMassY;
    }
    return 0.f;
}


