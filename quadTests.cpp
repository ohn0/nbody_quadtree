#include "quadtree.h"
#include <iostream>
bool insertIntoQuad();
bool insertIntoQuadFailsWhenElementExists();
bool validQuadrantIsNotNULL();
bool validQuadrantIsFound();

int main(int argc, char** argv)
{
    if(insertIntoQuad() && insertIntoQuadFailsWhenElementExists()
       && validQuadrantIsNotNULL() && validQuadrantIsFound()){
        std::cout << "------------------All tests passed!------------------" << std::endl;
        return 0;
    }else{
        std::cout << "Test(s) failed." << std::endl;
        return -1;
    }
}

bool insertIntoQuad()
{
    quadtree<quadNode> Q(0,0, 100, 100);
    quadNode Qnode;
    Q.insertElement(&Qnode, 10.f, 10.f);
    if(Q.getValue() == nullptr){
        std::cout << "Inserted into quadtree but value is not in quadtree." << std::endl;
        return false;
    }
    std::cout << "insertIntoQuad PASSED" << std::endl;
    return true;
}

bool insertIntoQuadFailsWhenElementExists()
{
    quadtree<quadNode> Q(0, 0, 100, 100);
    quadNode node;
    quadNode nodeB;
    Q.insertElement(&node, 10.f, 10.f);
    Q.insertElement(&nodeB, 80.f, 40.f);
    if(&nodeB == Q.getValue()){
        std::cout << "New element that was inserted into the quadtree is in the root, it should be" <<
                  " a child of the root." << std::endl;
        return false;
    }
    std::cout << "insertIntoQuadFailsWhenElementExists PASSED" << std::endl;
    return true;
}

bool validQuadrantIsNotNULL()
{
    quadtree<quadNode> Q(0, 0, 100, 100);
    quadNode node;
    quadNode nodeB;
    Q.insertElement(&node, 10.f, 10.f);
    Q.insertElement(&nodeB, 21.f, 40.f);
    quadtree<quadNode>** quadNodes = Q.getQuads();
    int i;
    for(i = 0; i < 4; i++){
        if(quadNodes[i] == nullptr){
            std::cout << "Root's children are not initialized" << std::endl;
            return false;
        }
    }
    std::cout << "validQuadrantIsNotNULL PASSED" << std::endl;
    return true;
}

bool validQuadrantIsFound()
{
    quadtree<quadNode> Q(0,0, 100, 100);
    quadNode node;
    quadNode nodeB;
    Q.insertElement(&node, 10.f, 10.f);
    Q.insertElement(&nodeB,11.f, 10.f);

    if(Q.getValue() == nullptr){
        std::cout << "validQuadrantIsFound PASSED" << std::endl;
        return true;
    }

    std::cout << "Root's element did not get inserted into one of it's" <<
                 " children." << std::endl;
    return false;

}


