
#ifndef EDGE_H
#define EDGE_H

#include "../HalfEdge_structure/vertex.h"

class Node;


class Edge {

protected:
    Vertex* _centerofSrcPlane;
    Vertex* _centerOfDestPlane;
    double _edgeWeight;

public:
    // Constructors
    Edge();
    Edge(Vertex *src, Vertex *target, double weight);
    Edge(Vertex *src, Vertex *target);
    Edge(Vertex* target, double weight);
    Edge(Vertex* target);
    Edge(double weight);

    // Getters
    Vertex* getTargetVertex(){ return _centerOfDestPlane; }
    Vertex* getSrcVertex()   { return _centerofSrcPlane; }
    const double getWeight() { return _edgeWeight; }

    // Setters
    void setTargetVertex(Vertex* v)  { _centerOfDestPlane = v; }
    void setEdgeWeight(double weight){ _edgeWeight = weight; }

    // Other functions
    void display();

};

#endif
