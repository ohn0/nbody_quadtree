#include "quadtree.h"
#include <iostream>
bool insertIntoQuad();
bool insertIntoQuadFailsWhenElementExists();
bool validQuadrantIsNotNULL();
bool validQuadrantIsFound();
bool existingElementIsDeleted();
bool existingElementIsFound();
bool nonexistentElementNotFound();
bool deletingNonExistentElementDoesNothing();
int main(int argc, char** argv)
{
    if(insertIntoQuad() && insertIntoQuadFailsWhenElementExists()
       && validQuadrantIsNotNULL() && validQuadrantIsFound()
       && existingElementIsFound() && nonexistentElementNotFound()
       && existingElementIsDeleted() && deletingNonExistentElementDoesNothing()){
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
    Q.insertElement(new quadNode, 43, 67);
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

bool existingElementIsDeleted()
{
    quadtree<quadNode> Q(0,0, 100, 100);
    quadNode A,B,C,D;
    Q.insertElement(&A, 77,21);
    Q.insertElement(&B, 37,84);
    Q.insertElement(&C, 67,92);
    Q.insertElement(&D, 12,9);

    int deleteResult = Q.deleteNode(77,21);
    if(deleteResult == -1){
        std::cout << "Unable to delete element." << std::endl;
        return false;
    }

    quadtree<quadNode>** foundNode = Q.findNode(77, 21);
    if(foundNode != nullptr){
        printf("%p, %p", *foundNode, &A);
        std::cout << "Node that was deleted still exists in quadtree." << std::endl;
        return false;
    }

    std::cout << "existingElementIsDeleted PASSED" << std::endl;
    return true;
}

bool deletingNonExistentElementDoesNothing()
{
    quadtree<quadNode> Q(0,0,100,100);
    quadNode A, B;
    if(Q.deleteNode(12,12) != -1){
        std::cout << "Quadtree tried to delete something from an empty quadtree." << std::endl;
        return false;
    }
    Q.insertElement(&A, 12,12);
    Q.insertElement(&B, 66,87);
    if(Q.deleteNode(23,23) != -1){
        std::cout << "Quadtree tried to delete an element that doesn't exist in the quadtree." << std::endl;
        return false;
    }

    if(Q.deleteNode(12,2) != -1 && Q.deleteNode(66,87) == -1 && Q.deleteNode(0,3) != -1){
        std::cout << "Series of deletions messed up the quadtree." << std::endl;
        return false;
    }
    std::cout << "deletingNonExistentElementDoesNothing PASSED" << std::endl;
    return true;
}

bool existingElementIsFound()
{
    quadtree<quadNode> Q(0,0,100,100);
    quadNode A,B;
    Q.insertElement(&A, 12, 44);
    Q.insertElement(&B, 66, 89);
    quadtree<quadNode>* node = *(Q.findNode(12, 44));
    if(node == nullptr){
        std::cout << "Unable to find node that was just inserted." << std::endl;
        return false;
    }

    std::cout << "existingElementIsFound PASSED" << std::endl;
    return true;
}

bool nonexistentElementNotFound()
{
    quadtree<quadNode> Q(0,0,100,100);
    quadNode A,B;
    Q.insertElement(&A, 12, 44);
    Q.insertElement(&B, 42, 23);
    quadtree<quadNode>** node = (Q.findNode(32,44));
    if(node != nullptr){
        std::cout << "Node that doesn't exist in quadtree found in quadtree." << std::endl;
        return false;
    }
    std::cout << "nonexistentElementNotFound PASSED" << std::endl;
    return true;
}


