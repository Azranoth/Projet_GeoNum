#ifndef NODE_H
#define NODE_H


#include <Eigen/Dense>
#include <map>

#include "Edge.h"
#include "../Plane_lib/Plane.h"

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
    Plane* _plane;                                              // plane center
    std::map<int, Edge*, classCompEdges> _listOfEdges;          // list of the edges with this node as source
    std::map<int, Edge*, classCompEdges> _edgesToThis;          // list of the edges with this node as a target (used in planes orientation process)
    bool _alreadyOriented;                                      // boolean used in orientNormalsMap (determine if this node has already been processed or not)


public:
    // Constructors
    Node();
    Node(Vector3d normalVector, Vertex* center, std::map<int, Edge*, classCompEdges> map);
    Node(Vector3d normalVector, Vertex* center);
    Node(Vector3d normalVector);
    Node(Vertex* center);
    Node(Plane* plane0);

    // Getters
    Vector3d getNormal()                                    { return _plane->normal(); }
    Vertex* getCenter()                                     { return _plane->center(); }
    Plane* getPlane()                                       { return _plane;           }
    std::map<int, Edge*, classCompEdges> getEdges()         { return _listOfEdges;     }
    std::map<int, Edge*, classCompEdges> getEdgesToThis()   { return _edgesToThis;     }
    bool isOriented()                                       { return _alreadyOriented; }

    // Setters
    void setNormal(Vector3d newNormal)                       { _plane->normal(newNormal); }
    void setCenter(Vertex* newCenter)                        { _plane->center(newCenter); }
    void setEdges(std::map<int, Edge*, classCompEdges> list) { _listOfEdges = list;       }
    void setOriented()                                       { _alreadyOriented = true;   }

    // Other methods

    /**
     * @brief display   displays the node in text form on the standard output
     */
    void display();

    /**
     * @brief display   displays the graph in text form on the standard output (recursive way)
     */
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

    /**
     * @brief addEdgePointingToThisPlane add an Edge object taking source in src Node and pointing this Node object
     * @param src
     */
    void addEdgePointingToThisPlane(Node* src);

    /**
     * @brief addEdgePointingToThisPlane add an Edge object of weight weight taking source in src Node and pointing this Node object
     * @param src
     * @param weight
     */
    void addEdgePointingToThisPlane(Node* src, double weight);

    /**
     * @brief orientNormalsMap  Recursively process the nodes linked by edges to this node to re-orient normals of planes when it's required
     * @param map
     * @param parentCalling
     */
    void orientNormalsMap(std::map<int, Node*, classCompNodes> map, int parentCalling);

};

#endif
