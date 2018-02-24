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

struct classCompNodes
{
    bool operator() (const int& id1, const int& id2) const
    { return id1<id2; }
};

/**
 * @brief The Node class represents a plane object included in a graph
 */
class Node {

protected:
    Vector3d _normalVector;                                     // plane's vector
    Vertex*  _planeCenter;                                      // plane's center
    std::map<int, Edge*, classCompEdges> _listOfEdges;          // list of the edges with this node as source
    std::map<int, Edge*, classCompEdges> _edgesToThis;          // list of the edges with this node as a target (used in planes orientation process)
    bool _alreadyOriented;
    bool _ntmMap = false;


public:
    // Constructors
    Node();
    Node(Vector3d normalVector, Vertex* center, std::map<int, Edge*, classCompEdges> map);
    Node(Vector3d normalVector, Vertex* center);
    Node(Vector3d normalVector);
    Node(Vertex* center);

    // Getters
    Vector3d getNormal()                                    { return _normalVector; }
    Vertex* getCenter()                                     { return _planeCenter; }
    std::map<int, Edge*, classCompEdges> getEdges()         { return _listOfEdges; }
    std::map<int, Edge*, classCompEdges> getEdgesToThis()   { return _edgesToThis; }
    bool isOriented()                                       { return _alreadyOriented; }

    // Setters
    void setNormal(Vector3d newNormal)                       { _normalVector = newNormal; }
    void setCenter(Vertex* newCenter)                        { _planeCenter = newCenter; }
    void setEdges(std::map<int, Edge*, classCompEdges> list) { _listOfEdges = list; }
    void setOriented()                                       { _alreadyOriented = true; }

    // Other functions
    void display();
    void display2();

    /**
     * @brief addEdge add an Edge object pointing to the Node n to the list of this object
     * @param n
     */
    void addEdge(Node* n);

    /**
     * @brief addEdge add an Edge object of weight weight pointing to the Node n of this object
     * @param n
     * @param weight
     */
    void addEdge(Node* n, double weight);


    void addEdgePointingToThisPlane(Node* src);

    void addEdgePointingToThisPlane(Node* src, double weight);


    //void orientNormals(Node* parentCalling);

    void orientNormalsMap(std::map<int, Node*, classCompNodes> map, int parentCalling);
};

#endif
