
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

    /**
     * @brief getTargetPlane    returns the Node object pointed by this Edge
     * @return
     */
    Node* getTargetPlane(){ return _destPlane; }

    /**
     * @brief getSrcPlane       returns the Node object in which this Edge takes source
     * @return
     */
    Node* getSrcPlane()   { return _srcPlane; }

    /**
     * @brief getWeight     returns the weight of this Edge
     * @return
     */
    const double getWeight() { return _edgeWeight; }

    // Setters

    /**
     * @brief setTargetPlane    sets this Edge's target plane (i.e the Node object containing it)
     * @param v
     */
    void setTargetPlane(Node* n)  { _destPlane = n; }

    /**
     * @brief setSourcePlane    sets this Edge's source plane (i.e the Node object containing it)
     * @param n
     */
    void setSourcePlane(Node* n)  { _srcPlane  = n; }

    /**
     * @brief setEdgeWeight     sets this Edge's weight
     * @param weight
     */
    void setEdgeWeight(double weight){ _edgeWeight = weight; }


    // Other methods

    /**
     * @brief display   displays the edge in text form on the standard output
     */
    void display();

};

#endif
