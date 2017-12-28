#ifndef NBODY_H
#define NBODY_H
#include <string>
#include <iostream>
#include <fstream>
#include "../quadtree.h"
const double GRAV_CONST = 6.674E-11;
#ifndef PARTICLE_STRUCT_H
#define PARTICLE_STRUCT_H
struct particle{
    int xPos = 0;
    int yPos = 0;

    double xVelocity = 0.f;
    double yVelocity = 0.f;

    double xAccel = 0.f;
    double yAccel = 0.f;

    double forceX = 0.f;
    double forceY = 0.f;

    double mass = 0.f;
};

#ifndef QUAD_NODE_STRUCT_H
#define QUAD_NODE_STRUCT_H
struct quadNode
{
    double massOfChildren = 0.f;
    double centerOfMassX = 0.f;
    double centerOfMassY = 0.f;
    particle* particleNode = nullptr;
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
        const particle* getParticles(){return this->particles;}
        int getParticleNum(){return this->numParticles;}
        int updateQuadTree();
        quadtree<quadNode>* getQuadTree(){return (this->Qtree);}
        int simulate(double);
        int updateNetForce();
        virtual ~nBody();

    protected:

    private:
        int numParticles, fieldWidth, fieldHeight;
        particle* particles;
        int calculateNetForce(particle*, quadtree<quadNode>*);
        int updateAcceleration(particle*);
        int updateVelocity(particle*, double);
        int updatePosition(particle*, double);
        quadNode* quadNodes;
        quadtree<quadNode>* Qtree;
        double calculationThreshold = 0.5f;
//        quad
};

#endif // NBODY_H
