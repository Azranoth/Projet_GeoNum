
#ifndef PLANESGRAPH_H
#define PLANESGRAPH_H


#include "Node.h"
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

    // Getters
    std::map<int, Node*, classCompNodes> getNodes(){ return _listOfNodes; }

    // Other functions
    void display();
    void display2();

    /**
     * @brief addNode adds a Node object n to the nodes list
     * @param n
     */
    void addNode(Node* n);


    Node* getMaxZPoint();

    /**
     * @brief kruskal generate the minimum spanning tree of this graph object using Boost library
     * @return a new graph object
     */
    PlanesGraph* kruskal();
};


#endif
