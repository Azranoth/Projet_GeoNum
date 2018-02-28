
#ifndef PLANESGRAPH_H
#define PLANESGRAPH_H


#include "Node.h"
#include "kDTree.h"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/kruskal_min_spanning_tree.hpp"

#include <algorithm>
#include <vector>

using namespace boost;
class Node;


/**
 * @brief The PlanesGraph class represents graphs of planes
 */
class PlanesGraph {

protected:
    std::map<int, Node*, classCompNodes> _listOfNodes;  // List of this graph's nodes

public:
    // Constructors
    PlanesGraph();
    PlanesGraph(std::map<int, Node*, classCompNodes> map);
    PlanesGraph(std::vector<Plane*> planes, int k);

    // Getters

    /**
     * @brief getNodes  returns the map of all the nodes in this graph
     * @return
     */
    std::map<int, Node*, classCompNodes> getNodes(){ return _listOfNodes; }

    // Other methods

    /**
     * @brief display   displays the graph in text form on the standard output
     */
    void display();

    /**
     * @brief addNode adds a Node object n to the nodes list
     * @param n
     */
    void addNode(Node* n);


    /**
     * @brief kruskal generate the minimum spanning tree of this graph object using Boost library, then automatically
     * re-orient planes if required
     * @return a vector of each planes in the mesh
     */
    std::vector<Plane*> kruskal();
};


#endif
