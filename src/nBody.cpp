#include "nBody.h"

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
    line 0:numberOfParticles
    line 1:                 xPosition yPosition xVelocity yVelocity xAcceleration yAcceleration mass
    .
    .
    .
    line numberOfParcticles:xPosition yPosition xVelocity yVelocity xAcceleration yAcceleration mass
    */

    std::ifstream particleFile(filename);
    if(!particleFile.is_open()){
        printf("Error opening %s.\n", filename.c_str());
    }
    else{
        particleFile >> numParticles;
        this->particles = new particle[numParticles];
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
            i++;
        }
    }
}

double calculateMassOfChildren(quadtree<quadNode>* Q)
{
    if(!Q->isExternalNode()){
        Q->getValue()->massOfChildren = 0.f;
        for(int i = 0; i < 4; i++){
            Q->getValue()->massOfChildren += calculateMassOfChildren(Q->getQuads()[i]);
        }
        return Q->getValue()->massOfChildren;

    }else{
        return Q->getValue()->particleNode->mass;
    }
}

double calculateCenterOfMassX(quadtree<quadNode>* Q)
{
    if(Q->getValue()->particleNode != nullptr){
        Q->getValue()->centerOfMassX = 0.f;
        for(int i = 0; i < 4; i++){
            Q->getValue()->centerOfMassX += calculateCenterOfMassX(Q->getQuads()[i]);
        }
        Q->getValue()->centerOfMassX = Q->getValue()->centerOfMassX/Q->getValue()->massOfChildren;
        return Q->getValue()->centerOfMassX;
    }else{
        return Q->getValue()->particleNode->mass * Q->getValue()->particleNode->xPos;
    }
}

double calculateCenterOfMassY(quadtree<quadNode>* Q)
{
    if(Q->getValue()->particleNode != nullptr){
        Q->getValue()->centerOfMassY = 0.f;
        for(int i = 0; i < 4; i++){
            Q->getValue()->centerOfMassY += calculateCenterOfMassY(Q->getQuads()[i]);
        }
        Q->getValue()->centerOfMassY = Q->getValue()->centerOfMassY/Q->getValue()->massOfChildren;
        return Q->getValue()->centerOfMassY;
    }else{
        return Q->getValue()->particleNode->yPos * Q->getValue()->particleNode->mass;
    }
}
