#ifndef NODE_H
#define NODE_H


#include <Eigen/Dense>

#include "Edge.h"
#include <map>

class Edge;
class Vertex;

using namespace Eigen;

struct classCompEdges
{
    bool operator() (const int& e1, const int& e2) const
    { return e1 < e2; }
};

class Node {

protected:
    Vector3d _normalVector;
    Vertex* _planeCenter;
    std::map<int, Edge*, classCompEdges> _listOfEdges;

public:
    // Constructors
    Node();
    Node(Vector3d normalVector, Vertex* center, std::map<int, Edge*, classCompEdges> map);
    Node(Vector3d normalVector, Vertex* center);
    Node(Vector3d normalVector);
    Node(Vertex* center);

    // Getters
    Vector3d getNormal()                     { return _normalVector; }
    Vertex* getCenter()                      { return _planeCenter; }
   std::map<int, Edge*, classCompEdges> getEdges(){ return _listOfEdges; }

    // Setters
    void setNormal(Vector3d newNormal)                  { _normalVector = newNormal; }
    void setCenter(Vertex* newCenter)                   { _planeCenter = newCenter; }
    void setEdges(std::map<int, Edge*, classCompEdges> list) { _listOfEdges = list; }

    // Other functions
    void display();
    void addEdge(Node* n);
    void addEdge(Node* n, double weight);

};

#endif
