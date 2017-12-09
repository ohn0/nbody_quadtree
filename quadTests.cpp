#include "quadtree.h"
#include <iostream>
bool insertIntoQuad();
bool insertIntoQuadFailsWhenElementExists();
bool validQuadrantIsNotNULL();

int main(int argc, char** argv)
{
    if(insertIntoQuad() && insertIntoQuadFailsWhenElementExists() && validQuadrantIsNotNULL()){
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
    Q.insertElement(&nodeB);
    if(&nodeB == Q.getValue()){
        std::cout << "New element that was inserted into the quadtree is in the root, it should be" <<
                  " a child of the root." << std::endl;
        return false;
    }
    return true;
}

bool validQuadrantIsNotNULL()
{
    quadtree<quadNode> Q(0, 0, 100, 100);
    quadNode node;
    quadNode nodeB;
    Q.insertElement(&node);
    Q.insertElement(&nodeB);
    quadtree<quadNode>** quadNodes = Q.getQuads();
    int i;
    for(i = 0; i < 4; i++){
        if(quadNodes[i] == nullptr){
            std::cout << "Root's children are not initialized" << std::endl;
            return false;
        }
    }
    return true;
}


