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
    int getId() const { return _id; }
    double x() const { return _x; }
    double y() const { return _y; }
    double z() const { return _z; }
    HalfEdge* getChildEdge(){ return _childEdge; }

    // Setters
    void setChildEdge(HalfEdge* he);
    void xyz(double x0, double y0, double z0);

    // Other functions
    void display();
    static void resetNbVertices();
    double barycentricArea();
    double voronoiArea();

    // Operators overload
    bool operator==(Vertex& other);
};

#endif // VERTEX_H
