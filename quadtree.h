#ifndef QUADTREE_H
#define QUADTREE_H
#include <iostream>
#define NULL 0
struct quadNode
{
    double massOfChildren;
    double centerOfMassX;
    double centerOfMassY;
};
template <typename T>
class quadtree
{
    int sizeX, startX;
    int sizeY, startY;
    T* value;
    public:
        quadtree();
        quadtree(int,int,int,int);
        T* getValue();
        quadtree<T>** getQuads();
        int insertElement(T*);
        virtual ~quadtree();


    protected:

    private:
        quadtree<T>* NW = nullptr;
        quadtree<T>* NE = nullptr;
        quadtree<T>* SW = nullptr;
        quadtree<T>* SE = nullptr;
        quadtree<T>* findValidQuadrant(double, double);
        int subdivide();
        quadtree<T>* quads[4] = {NW, NE, SW, SE};

};


template <typename T> quadtree<T>::quadtree()
{
    this->value = NULL;
}

template <typename T> quadtree<T>::quadtree(int startX, int startY, int sizeX, int sizeY)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->startX = startX;
    this->startY = startY;
    this->value = NULL;
}

template <class T> quadtree<T>::~quadtree()
{
    delete NW;
    delete NE;
    delete SW;
    delete SE;
}


template <class T> quadtree<T>** quadtree<T>::getQuads()
{
    return this->quads;
}

template <class T> T* quadtree<T>::getValue()
{
    return this->value;
}

template <class T> int quadtree<T>::insertElement(T* element)
{
    /*

    */
    if(this->value != nullptr){
        this->subdivide();
        return 0;
    }else{
        this->value = element;
        return 0;
    }
    return -1;
}

template <class T> int quadtree<T>::subdivide()
{
    this->NW = new quadtree<T>(this->startX, this->startY,
                               this->startX/2, this->startY/2);
    this->NE = new quadtree<T>(this->startX/2, this->startY,
                               this->startX/2, this->startY/2);
    this->SW = new quadtree<T>(this->startX, this->startY/2,
                               this->startX/2, this->startY/2);
    this->SE = new quadtree<T>(this->startX/2, this->startY/2,
                               this->startX/2, this->startY/2);
}

template <class T> quadtree<T>* quadtree<T>::findValidQuadrant(double X, double Y)
{
    if(NW == NULL && NE == NULL &&
       SW == NULL && SE == NULL){
        std::cout << "Quadrants not initialized." << std::endl;
        return NULL;
    }
    return NULL;
}

#endif // QUADTREE_H
