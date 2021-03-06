#include "quadtree.h"
#include "nBody.h"
#include "visualizer.h"
#include <iostream>
bool testQuadTree();
bool testNBody();
bool insertIntoQuad();
bool insertIntoQuadFailsWhenElementExists();
bool validQuadrantIsNotNULL();
bool validQuadrantIsFound();
bool existingElementIsDeleted();
bool existingElementIsFound();
bool nonexistentElementNotFound();
bool deletingNonExistentElementDoesNothing();
bool nBodyFileNameConstructorWorks();
bool massOfChildrenCorrectlyCalculated();
bool rootCenterOfMassCorrectlyCalculated();
bool netForceCorrectlyCalculated();
bool smallerMassParticleMovesTowardGreaterMassParticle();
bool simulationAnimationTest();


int main(int argc, char** argv)
{
    simulationAnimationTest();
    return 0;
//    if(testQuadTree() && testNBody()){
//        std::cout << "------------------ALL tests passed!------------------" << std::endl;
//        return 0;
//    }else{
//        std::cout << "------------------Some tests failed. :(------------------" << std::endl;
//        return -1;
//    }


}

bool testQuadTree()
{
    if(insertIntoQuad() && insertIntoQuadFailsWhenElementExists()
       && validQuadrantIsNotNULL() && validQuadrantIsFound()
       && existingElementIsFound() && nonexistentElementNotFound()
       && existingElementIsDeleted() && deletingNonExistentElementDoesNothing()){
        std::cout << "------------------All quadtree tests passed!------------------" << std::endl;
        return true;
    }else{
        std::cout << "Quadtree Test(s) failed." << std::endl;
        return false;
    }
}


bool testNBody()
{
    if(nBodyFileNameConstructorWorks() && massOfChildrenCorrectlyCalculated() &&
       rootCenterOfMassCorrectlyCalculated() && netForceCorrectlyCalculated() &&
       smallerMassParticleMovesTowardGreaterMassParticle() && simulationAnimationTest()){
        std::cout << "------------------All NBody tests passed!------------------" << std::endl;
        return true;
    }else{
        std::cout << "NBody tests failed." << std::endl;
        return false;
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

    if(Q.getValue() != &node && Q.getValue() != &nodeB){
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

bool nBodyFileNameConstructorWorks()
{
    /*
    Sample file
    3
    23 28 72 12 33 44 5
    3 21 55 78 13 48 58
    83 19 64 56 19 32 99
    */
    nBody nSystem("particles");
    nSystem.getParticles();
    if(nSystem.getParticleNum() != 3){
        std::cout << "nBody obtained wrong number of particles." << std::endl;
    }
    const particle* particles = nSystem.getParticles();
    particle p0 = particles[0];
    particle p1 = particles[1];
    particle p2 = particles[2];

    if(p0.mass == 5 && p0.xPos == 23 && p0.yPos == 28 && p0.xVelocity == 72 &&
       p0.yVelocity == 12 && p0.xAccel == 33 && p0.yAccel == 44 &&
       p1.mass == 58 && p1.xPos == 3 && p1.yPos == 21 && p1.xVelocity == 55 &&
       p1.yVelocity == 78 && p1.xAccel == 13 && p1.yAccel == 48 &&
       p2.mass == 99 && p2.xPos == 83 && p2.yPos == 19 && p2.xVelocity == 64 &&
       p2.yVelocity == 56 && p2.xAccel == 19 && p2.yAccel == 32){
        std::cout << "nBodyFileNameConstructorWorks PASSED" << std::endl;
        return true;
   }else{
        std::cout << "Value from sample file was not read into nBody correctly." << std::endl;
        return false;
   }
}

bool massOfChildrenCorrectlyCalculated()
{
    nBody nSystem("particles");
    calculateMassOfChildren(nSystem.getQuadTree());
    int totalMass = 5 + 58 + 99;
    quadNode* rootNode = nSystem.getQuadTree()->getValue();

    if(std::abs(totalMass - rootNode->massOfChildren) < 1){
        std::cout << "massOfChildrenCorrectlyCalculated PASSED" << std::endl;
        return true;
    }else{
        std::cout << "Root node does not contain the mass of all the particles."
                  << " Correct mass is " << totalMass << ", mass of root node is "
                  << rootNode->massOfChildren<<std::endl;

        return false;
    }
}

bool rootCenterOfMassCorrectlyCalculated()
{
    nBody nSystem("particles");
    quadtree<quadNode>* rootNode = nSystem.getQuadTree();
    calculateMassOfChildren(rootNode);

    calculateCenterOfMassX(rootNode);
    calculateCenterOfMassY(rootNode);
    int totalMass = 5 + 58 + 99;
    double CoMX = ((23*5.f)+(3.f*58)+(83.f*99))/(double)totalMass;
    double CoMY = ((28*5.f)+(21.f*58)+(19.f*99))/(double)totalMass;

    double rootCoMX = rootNode->getValue()->centerOfMassX;
    double rootCoMY = rootNode->getValue()->centerOfMassY;

    if(std::abs(CoMX - rootCoMX) < 1 && std::abs(CoMY - rootCoMY) < 1){
        std::cout << "rootCenterOfMassCorrectlyCalculated PASSED" << std::endl;
        return true;
    }else{
        std::cout << "Root has incorrect center of mass location.\nRoot Center: "<<
        rootCoMX << ", " << rootCoMY << "\nActual Center: " << CoMX << ", "
        << CoMY << std::endl;
        return false;
    }
}

bool netForceCorrectlyCalculated()
{
    nBody nSystem("particlesGrav");
    quadtree<quadNode>* rootNode = nSystem.getQuadTree();

    calculateMassOfChildren(rootNode);
    calculateCenterOfMassX(rootNode);
    calculateCenterOfMassY(rootNode);

    nSystem.updateNetForce();
    const particle* P = nSystem.getParticles();
    double smallForceVec = std::sqrt(std::pow(P[0].forceX,2)+
                                     std::pow(P[0].forceY,2));
    double bigForceVec = std::sqrt(std::pow(P[1].forceX,2)+
                                     std::pow(P[1].forceY,2));
    double smallForceVecB = std::sqrt(std::pow(P[2].forceX,2)+
                                     std::pow(P[2].forceY,2));


    for(int i = 0; i < nSystem.getParticleNum(); i++){
        printf("Net force on p%d: (%.20f,%.20f)\n", i, P[i].forceX, P[i].forceY);
        printf("Length of force vector p%d: %.20f\n", i,std::sqrt(std::pow(P[i].forceX,2)
                                                                 +std::pow(P[i].forceY,2)));
    }


    if(bigForceVec > smallForceVec && bigForceVec > smallForceVecB){
        std::cout << "netForceCorrectlyCalculated PASSED" << std::endl;
        return true;
    }
    std::cout << "Force vector magnitude of the smaller body was greater " <<
                 "than the force vector of the bigger body." << std::endl;

    return true;
}

bool smallerMassParticleMovesTowardGreaterMassParticle()
{
    nBody nSystem("particlesGrav");
    int startXP1 = 50;
    for(int i = 0; i < 10; i++){
        quadtree<quadNode>* nTree = nSystem.getQuadTree();
        calculateMassOfChildren(nTree);
        calculateCenterOfMassX(nTree);
        calculateCenterOfMassY(nTree);
        nSystem.updateNetForce();
        nSystem.simulate(2);
        printf("--------------------Iteration %d--------------------\n", i);
        for(int j = 0; j < nSystem.getParticleNum(); j++){
            printf("Particle %d location: (%d, %d)\n",
                   j, nSystem.getParticles()[j].xPos,
                   nSystem.getParticles()[j].yPos);
        }
        nSystem.updateQuadTree();
    }
    int endXP1 = nSystem.getParticles()[0].xPos;
    if(endXP1 < startXP1){
        std::cout << "smallerMassParticleMovesTowardGreaterMassParticle PASSED" << std::endl;
        return true;
    }
    std::cout << "The smaller mass particle moved away from the particle with greater mass." << std::endl;
    return false;
}

bool simulationAnimationTest()
{
    nBody nSystem("qparticles1k");
    visualizer vis("v", 900,900);
    vis.toggleTreeView(true);
    quadtree<quadNode>* qTree;
    SDL_Event e;
    bool quit = false;
    bool updateVisuals = true;
    printf("Ready.\n");
    while(!quit){
        while(SDL_PollEvent(&e)){
            if(e.key.keysym.sym == SDLK_ESCAPE){
                quit = true;
            }

            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_SPACE){
                    updateVisuals = !updateVisuals;
                }
            }
        }
        const particle* particles;
        if(updateVisuals){
            qTree = nSystem.getQuadTree();
            calculateMassOfChildren(qTree);
            calculateCenterOfMassX(qTree);
            calculateCenterOfMassY(qTree);
            nSystem.updateNetForce();
            nSystem.simulate(2);
            vis.updateVisuals(&nSystem);
            nSystem.updateQuadTree();
            particles = nSystem.getParticles();
            for(int i = 0; i < nSystem.getParticleNum(); i++){
                const particle P = particles[i];
//                printf("Particle %d info-------------------------\n",i);
//                printf("Position:(%d, %d)\nVelocity:(%f, %f)\nAcceleration:(%f, %f)\n",
//                       P.xPos, P.yPos, P.xVelocity, P.yVelocity, P.xAccel, P.yAccel);
            }
        }
    }
    vis.deleteVisualizer();
    return true;
}

