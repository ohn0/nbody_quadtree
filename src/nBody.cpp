#include "../include/nBody.h"

nBody::nBody()
{
    //ctor
}

nBody::~nBody()
{
    //dtor
    delete[] particles;
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
        Qtree = quadtree<quadNode>(0,0,fieldWidth, fieldHeight);
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
        particleFile.close();
        this->generateQuadTree();
    }
}

int nBody::generateQuadTree()
{
    for(int i = 0; i < this->numParticles; i++){
        if(Qtree.insertElement(&quadNodes[i], quadNodes[i].particleNode->xPos,
                            quadNodes[i].particleNode->yPos) == -1){
            printf("Problem encountered attempting to insert particle into quadtree.\n");
            return -1;
        }
    }
    return 0;
}

int nBody::calculateNetForce(particle* P, quadtree<quadNode>* Q)
{

    if(Q->getValue() == nullptr){
        return 0;
    }
    if(Q->getValue()->particleNode->xPos == P->xPos &&
       Q->getValue()->particleNode->yPos == P->yPos){
        return 0;
    }

    double distance, Xdist, Ydist, gravNetForce;
    if(Q->isExternalNode()){
        distance = std::sqrt(std::pow(P->xPos - Q->getValue()->particleNode->xPos, 2) +
                             std::pow(P->yPos - Q->getValue()->particleNode->yPos,2));
        particle* qParticle = Q->getValue()->particleNode;
        Xdist = P->xPos - qParticle->xPos;
        Ydist = P->yPos - qParticle->yPos;
        gravNetForce = (GRAV_CONST * P->mass * qParticle->mass) / distance;

        P->forceX += (gravNetForce * Xdist);
        P->forceY += (gravNetForce * Ydist);
        return 0;
    }

    distance = std::sqrt(std::pow(P->xPos - Q->getValue()->centerOfMassX, 2) +
                                std::pow(P->yPos - Q->getValue()->centerOfMassY,2));
    if(((double)Q->getsX())/distance > this->calculationThreshold){
        for(int i = 0; i < 4; i++){
            this->calculateNetForce(P, Q->getQuads()[i]);
        }
        return 0;
    }else{
        quadNode* node = Q->getValue();
        Xdist = P->xPos - node->centerOfMassX;
        Ydist = P->yPos - node->centerOfMassY;

        gravNetForce = (GRAV_CONST * P->mass * node->massOfChildren) / distance;

        P->forceX += (gravNetForce * Xdist);
        P->forceY += (gravNetForce * Ydist);

        return 0;
    }

    printf("Unable to calculate net force.\n");
    return -1;
}

double calculateMassOfChildren(quadtree<quadNode>* Q)
{
    printf("At %p\n", Q);
    if(!Q->isExternalNode()){
        printf("getting child mass\n");
        Q->getValue()->massOfChildren = 0.f;
        for(int i = 0; i < 4; i++){
            Q->getValue()->massOfChildren += calculateMassOfChildren(Q->getQuads()[i]);
        }
        return Q->getValue()->massOfChildren;

    }else{
        if(Q->getValue() != nullptr && Q->getValue()->particleNode != nullptr){
            printf("Returning %f\n", Q->getValue()->particleNode->mass);
            return Q->getValue()->particleNode->mass;
        }
        else{
            return 0.f;
        }
    }
}

double calculateCenterOfMassX(quadtree<quadNode>* Q)
{
    if(!Q->isExternalNode()){
        Q->getValue()->centerOfMassX = 0.f;
        for(int i = 0; i < 4; i++){
            Q->getValue()->centerOfMassX += calculateCenterOfMassX(Q->getQuads()[i]);
        }
        printf("CoMX is %f\n", Q->getValue()->centerOfMassX);
        Q->getValue()->centerOfMassX = Q->getValue()->centerOfMassX/Q->getValue()->massOfChildren;
        return Q->getValue()->centerOfMassX;
    }else{
        if(Q->getValue() != nullptr && Q->getValue()->particleNode != nullptr){
            return Q->getValue()->particleNode->mass * Q->getValue()->particleNode->xPos;
        }else{
            return 0.f;
        }
    }
}

double calculateCenterOfMassY(quadtree<quadNode>* Q)
{
    if(!Q->isExternalNode()){
        Q->getValue()->centerOfMassY = 0.f;
        for(int i = 0; i < 4; i++){
            Q->getValue()->centerOfMassY += calculateCenterOfMassY(Q->getQuads()[i]);
        }
        Q->getValue()->centerOfMassY = Q->getValue()->centerOfMassY/Q->getValue()->massOfChildren;
        return Q->getValue()->centerOfMassY;
    }else{
        if(Q->getValue() != nullptr && Q->getValue()->particleNode != nullptr){
            return Q->getValue()->particleNode->yPos * Q->getValue()->particleNode->mass;
        }else{
            return 0.f;
        }
    }
}


