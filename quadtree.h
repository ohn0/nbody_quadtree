#ifndef QUADTREE_H
#define QUADTREE_H
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
        const quadtree* getQuads();
        int insertElement(T*);
        virtual ~quadtree();


    protected:

    private:
        quadtree<T>* NW;
        quadtree<T>* NE;
        quadtree<T>* SW;
        quadtree<T>* SE;
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
    //dtor
}


template <class T> const quadtree<T>* quadtree<T>::getQuads()
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
    if(this->value != NULL){
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
    int i;
    for(i = 0; i < 4; i++){
        this->quads[i] = new quadtree<T>();
    }
}

#endif // QUADTREE_H
