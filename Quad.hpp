// From ChatGPT

#ifndef QUAD_H
#define QUAD_H

#include "Body.hpp"  //Body code

#include <iostream>
#include <cmath>
#include <vector>

const double G = 6.6743e-11; // gravitational constant

class Quad {
public:
    Quad(double x, double y, double size);
    ~Quad();

    bool isLeaf() const;
    void insert(Body* body);
    void updateForce(Body* body, double theta);
    void print() const;

private:
    int getIndex(double x, double y) const;

private:
    double x; // x-coordinate of the center of the quad
    double y; // y-coordinate of the center of the quad
    double size; // size of the quad, length of an edge
    double totalMass; // total mass of bodies in the quad
    double cx; // x-coordinate of the center of mass of bodies in the quad
    double cy; // y-coordinate of the center of mass of bodies in the quad
    bool hasBody; // tell if has body or not
    Quad* children[4]; // pointers to the child quads
};

#endif // QUAD_H