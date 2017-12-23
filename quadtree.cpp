#include "quadtree.h"
double calculateMassOfChildren(quadtree<quadNode>* Q)
{
    Q->value.massOfChildren = 0.f;
    if(!Q->isExternal){
        for(int i = 0; i < 4; i++){
            Q->value->massOfChildren += calculateMassOfChildren(Q->quads[i]);
        }
    }else{
        return Q->value->massOfChildren;
    }
}

double calculateCenterOfMassX(quadtree<quadNode>* Q)
{

}

double calculateCenterOfMassY(quadtree<quadNode>* Q)
{

}
