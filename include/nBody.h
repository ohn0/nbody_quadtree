#ifndef NBODY_H
#define NBODY_H
#include <string.h>
#include "../quadtree.h"

#ifndef PARTICLE_STRUCT_H
#define PARTICLE_STRUCT_H
struct particle{
    int xPos;
    int yPos;

    double xVelocity;
    double yVelocity;

    double xAccel;
    double yAccel;

    double mass;
};

#ifndef QUAD_NODE_STRUCT_H
#define QUAD_NODE_STRUCT_H
struct quadNode
{
    double massOfChildren;
    double centerOfMassX;
    double centerOfMassY;
    particle* particleNode;
};
#endif // QUAD_NODE_STRUCT_H

double calculateMassOfChildren(quadtree<quadNode>*);
double calculateCenterOfMassX(quadtree<quadNode>*);
double calculateCenterOfMassY(quadtree<quadNode>*);
#endif // PARTICLE_STRUCT_H

class nBody
{

    public:
        nBody();
        nBody(std::string);
        nBody(particle*);
        void setThreshold(double threshold){calculationThreshold = threshold;}

        virtual ~nBody();

    protected:

    private:
        particle* particles;
        quadtree<quadNode> Qtree;
        double calculationThreshold = 0.5f;
//        quad
};

#endif // NBODY_H
