#ifndef NBODY_H
#define NBODY_H
#include <string.h>
#include "../quadtree.h"
struct particle{
    int xPos;
    int yPos;

    float xVelocity;
    float yVelocity;

    float xAccel;
    float yAccel;

};

class nBody
{
    public:
        nBody();
        nBody(std::string);
        nBody()
        virtual ~nBody();

    protected:

    private:
        quad
};

#endif // NBODY_H
