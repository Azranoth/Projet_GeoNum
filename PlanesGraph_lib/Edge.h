
#ifndef EDGE_H
#define EDGE_H

#include "../HalfEdge_structure/vertex.h"
#include "Node.h"

class Node;


/**
 * @brief The Edge class represents an edge between 2 vertices
 */
class Edge {

protected:
    Node* _srcPlane;      // source plane of this edge
    Node* _destPlane;     // target plane of this edge
    double _edgeWeight;   // weight of this edge

public:
    // Constructors
    Edge();
    Edge(Node *src, Node *target, double weight);
    Edge(Node *src, Node *target);
    Edge(Node* target, double weight);
    Edge(Node* target);
    Edge(double weight);

    // Getters
    Node* getTargetPlane(){ return _destPlane; }
    Node* getSrcPlane()   { return _srcPlane; }
    const double getWeight() { return _edgeWeight; }

    // Setters
    void setTargetPlane(Node* v)  { _destPlane = v; }
    void setEdgeWeight(double weight){ _edgeWeight = weight; }

    // Other functions
    void display();

};

#endif
