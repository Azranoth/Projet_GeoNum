#ifndef VERTEX_H
#define VERTEX_H

#include <math.h>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#include "halfedge.h"

class HalfEdge;

class Vertex {

protected:
    static int NB_VERTICES;

protected:
    int _id;
    double _x, _y, _z;
    HalfEdge* _childEdge;

public:
    Vertex();
    Vertex(double x, double y, double z);
    Vertex(double x, double y, double z, HalfEdge* childEdge);

    // Getters
    int getId(){ return _id; }
    double x(){ return _x; }
    double y(){ return _y; }
    double z(){ return _z; }
    HalfEdge* getChildEdge(){ return _childEdge; }

    // Setters
    void setChildEdge(HalfEdge* he);

    // Other functions
    void display();
    double barycentricArea();
    double voronoiArea();
};

#endif // VERTEX_H
