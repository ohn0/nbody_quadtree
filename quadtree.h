#ifndef QUADTREE_H
#define QUADTREE_H
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#define NW 0
#define NE 1
#define SW 2
#define SE 3
#define MINIMUM_QUADRANT_X 2
#define MINIMUM_QUADRANT_Y 2

template <typename T>
class quadtree
{
    int sizeX, startX;
    double X, Y;
    int sizeY, startY;
    bool isExternal;
    int occupiedQuadrants;
    T* value;
    public:
        quadtree();
        quadtree(int,int,int,int);
        T* getValue();
        quadtree<T>** getQuads();
        bool isExternalNode(){return isExternal;}
        int getstX(){return startX;}
        int getstY(){return startY;}
        int getsX(){return sizeX;}
        int getsY(){return sizeY;}
        double getX(){return X;}
        double getY(){return Y;}
        quadtree<T>** findNode(int, int);
        int deleteNode(int, int);
        int insertElement(T*, double, double);
        void summary();
        virtual ~quadtree();


    protected:

    private:
        quadtree<T>* findValidQuadrant(double, double);
        int subdivide();
        quadtree<T>* quads[4];

};

template <typename T> quadtree<T>::quadtree()
{
    this->isExternal = true;
    this->value = nullptr;
}

template <typename T> quadtree<T>::quadtree(int stX, int stY, int szX, int szY)
{
//    printf("Creating a quadrant with size (%d, %d) at location (%d, %d)\n", szX, szY, stX, stY);
    this->isExternal = true;
    this->sizeX = szX;
    this->sizeY = szY;
    this->startX = stX;
    this->startY = stY;
    this->value = nullptr;
    this->occupiedQuadrants = 0;
    X = Y = 0.f;
}

template <class T> quadtree<T>::~quadtree()
{
    if(!this->isExternal){
        int i;
        for(i = 0; i < 4; i++){
            if(this->quads[i]->getValue() != nullptr && !this->quads[i]->isExternalNode()){
                delete this->quads[i]->getValue();
            }
            delete this->quads[i];
        }
    }
}


template <class T> quadtree<T>** quadtree<T>::getQuads()
{
    return this->quads;
}

template <class T> T* quadtree<T>::getValue()
{
    return this->value;
}

template <typename T> int quadtree<T>::deleteNode(int X, int Y)
{
    quadtree<T>** nodeToDeleteAddr = (this->findNode(X,Y)) ;
    if(nodeToDeleteAddr == nullptr){
        return -1;
    }
//    printf("About to delete node at address %p\n", nodeToDeleteAddr);
    (*nodeToDeleteAddr)->value = nullptr;
    (*nodeToDeleteAddr)->X =0.f;
    (*nodeToDeleteAddr)->Y =0.f;
    return 0;
}

template <typename T> quadtree<T>** quadtree<T>::findNode(int X, int Y)
{
    if(this->X != X && this->Y != Y && this->isExternal){return nullptr;}
    if(this->isExternal){return nullptr;}

    for(int i = 0; i < 4; i++){
        if(this->quads[i]->startX + this->quads[i]->sizeX >= X &&
           this->quads[i]->startX <= X &&
           this->quads[i]->startY + this->quads[i]->sizeY >= Y &&
           this->quads[i]->startY <= Y){
            if(this->quads[i]->X == X && this->quads[i]->Y == Y && this->quads[i]->isExternal){
                return &(this->quads[i]);
            }
            return this->quads[i]->findNode(X,Y);
       }
    }
    return nullptr;
}

template <class T> int quadtree<T>::insertElement(T* element, double X, double Y)
{
    /*

    */

//    printf("Inserting (%f, %f)\n", X, Y);
    if(this->value != nullptr && this->isExternal){
        if(this->subdivide() < 0){
            return -1;
        }
        this->isExternal = false;
        quadtree<T>* validRootQuad = this->findValidQuadrant(this->X, this->Y);
        validRootQuad->insertElement(this->value, this->X, this->Y);
        this->value = new T;
        quadtree<T>* validQuad = this->findValidQuadrant(X, Y);
        return validQuad->insertElement(element, X, Y);
        return 0;
    }else{
        if(!this->isExternal){
            return (this->findValidQuadrant(X, Y))->insertElement(element, X, Y);
        }
        this->value = element;
        this->X = X;
        this->Y = Y;
        return 0;
    }
    printf("Couldn't insert(%f, %f) ):\n", X, Y);
    return -1;
}

template <class T> int quadtree<T>::subdivide()
{
    /*
    Subdivides the calling quadtree into 4 quadtrees.
    */

    int halfSizeX = (int)std::ceil(this->sizeX/2.f);
    int halfSizeY = (int)std::ceil(this->sizeY/2.f);
    if(halfSizeX == 1 && this->sizeX == 1){
        return -1;
    }
    this->quads[NW] = new quadtree<T>(this->startX , this->startY,
                               halfSizeX, halfSizeY);
    this->quads[NE] = new quadtree<T>(this->startX + halfSizeX, this->startY,
                               halfSizeX, halfSizeY);
    this->quads[SW] = new quadtree<T>(this->startX, this->startY + halfSizeY,
                               halfSizeX, halfSizeY);
    this->quads[SE] = new quadtree<T>(this->startX + halfSizeX, this->startY+halfSizeY,
                               halfSizeX, halfSizeY);
    return 0;

}

template <class T> void quadtree<T>::summary()
{

}

template <class T> quadtree<T>* quadtree<T>::findValidQuadrant(double X, double Y)
{
    /*
    Find which quadrant the given pair will reside within.
    */
    if(this->isExternal){
        std::cout << "Quadrants not initialized." << std::endl;
        return nullptr;
    }

    int i;
    for(i = 0; i < 4; i++){
        if(this->quads[i]->startX <= X &&
          (this->quads[i]->startX + this->quads[i]->sizeX >= X) &&
           this->quads[i]->startY <= Y &&
          (this->quads[i]->startY + this->quads[i]->sizeY >= Y)){
                return this->quads[i];
           }
    }

    std::cout << "Unable to find a valid quadrant for the specified points." <<
                 " This shouldn't happen." << std::endl;
    return nullptr;
}

#endif // QUADTREE_H
