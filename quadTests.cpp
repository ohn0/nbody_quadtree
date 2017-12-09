#include "quadtree.h"
#include <iostream>
bool insertIntoQuad();
bool insertIntoQuadFailsWhenElementExists();

int main(int argc, char** argv)
{
    if(insertIntoQuad() && insertIntoQuadFailsWhenElementExists()){
        std::cout << "All tests passed!" << std::endl;
        return 0;
    }else{
        std::cout << "Test failed." << std::endl;
        return -1;
    }
}

bool insertIntoQuad()
{
    quadtree<quadNode> Q(0,0, 100, 100);
    quadNode Qnode;
    Q.insertElement(&Qnode);
    if(Q.getValue() == NULL){
        std::cout << "Inserted into quadtree but value is not in quadtree." << std::endl;
        return false;
    }
    return true;
}

bool insertIntoQuadFailsWhenElementExists()
{
    quadtree<quadNode> Q(0, 0, 100, 100);
    quadNode node;
    quadNode* nodeAddr;
    quadNode nodeB;
    Q.insertElement(&node);
    nodeAddr = Q.getValue();
    Q.insertElement(&nodeB);
    if(nodeAddr != Q.getValue()){
        std::cout << "Element the quadtree was holding has changed." << std::endl;
        return false;
    }
    return true;

}


