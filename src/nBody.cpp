#include "nBody.h"

nBody::nBody()
{
    //ctor
}

nBody::~nBody()
{
    //dtor
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
