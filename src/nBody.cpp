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
    }else{
        return Q->getValue()->massOfChildren;
    }
}

double calculateCenterOfMassX(quadtree<quadNode>* Q)
{

}

double calculateCenterOfMassY(quadtree<quadNode>* Q)
{

}
