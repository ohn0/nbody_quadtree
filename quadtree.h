#ifndef QUADTREE_H
#define QUADTREE_H
#include <iostream>
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
    double X, Y;
    int sizeY, startY;
    bool isExternal;
    T* value;
    public:
        quadtree();
        quadtree(int,int,int,int);
        T* getValue();
        quadtree<T>** getQuads();
        int insertElement(T*, double, double);
        virtual ~quadtree();


    protected:

    private:
        quadtree<T>* NW;
        quadtree<T>* NE;
        quadtree<T>* SW;
        quadtree<T>* SE;
        quadtree<T>* findValidQuadrant(double, double);
        int subdivide();
        /*
        quad[0] = northwest quadrant;
        quad[1] = northeast quadrant;
        quad[2] = southwest quadrant;
        quad[3] = southeast quadrant;
        */
        quadtree<T>* quads[4];

};


template <typename T> quadtree<T>::quadtree()
{
    this->isExternal = true;
    this->value = NULL;
}

template <typename T> quadtree<T>::quadtree(int startX, int startY, int sizeX, int sizeY)
{
    this->isExternal = true;
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->startX = startX;
    this->startY = startY;
    this->value = NULL;
    X = Y = 0.f;
}

template <class T> quadtree<T>::~quadtree()
{
    if(!this->isExternal){
        int i;
        for(i = 0; i < 4; i++){
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

template <class T> int quadtree<T>::insertElement(T* element, double X, double Y)
{
    /*

    */
    if(this->value != nullptr){
        this->subdivide();
        this->isExternal = false;
        quadtree<T>* validRootQuad = this->findValidQuadrant(this->X, this->Y);
        validRootQuad->insertElement(this->value, this->X, this->Y);
        this->value = nullptr;
        quadtree<T>* validQuad = this->findValidQuadrant(X, Y);
        validQuad->insertElement(element, X, Y);
        return 0;
    }else{
        this->value = element;
        this->X = X;
        this->Y = Y;
        return 0;
    }
    return -1;
}

template <class T> int quadtree<T>::subdivide()
{
    /*
    Subdivides the calling quadtree into 4 quadtrees.
    */
    this->quads[0] = new quadtree<T>(this->startX, this->startY,
                               this->startX/2, this->startY/2);
    this->quads[1] = new quadtree<T>(this->startX/2, this->startY,
                               this->startX/2, this->startY/2);
    this->quads[2] = new quadtree<T>(this->startX, this->startY/2,
                               this->startX/2, this->startY/2);
    this->quads[3] = new quadtree<T>(this->startX/2, this->startY/2,
                               this->startX/2, this->startY/2);
    return 0;

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
        if(this->quads[i]->startX < X &&
          (this->quads[i]->startX + this->quads[i]->sizeX > X) &&
           this->quads[i]->startY < Y &&
          (this->quads[i]->startY + this->quads[i]->sizeY > Y)){
                return this->quads[i];
           }
    }

    std::cout << "Unable to find a valid quadrant for the specified points." <<
                 " This shouldn't happen." << std::endl;
    return nullptr;
}

#endif // QUADTREE_H
