
#ifndef PLANESGRAPH_H
#define PLANESGRAPH_H


#include "Node.h"
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/kruskal_min_spanning_tree.hpp"
#include <algorithm>
#include <vector>

using namespace boost;
class Node;

struct classCompNodes
{
    bool operator() (const int& id1, const int& id2) const
    { return id1<id2; }
};



class PlanesGraph {

protected:
    std::map<int, Node*, classCompNodes> _listOfNodes;

public:
    // Constructors
    PlanesGraph();
    PlanesGraph(std::map<int, Node*, classCompNodes> map);

    // Getters
    std::map<int, Node*, classCompNodes> getNodes(){ return _listOfNodes; }

    // Other functions
    void display();
    void addNode(Node* n);
    PlanesGraph* kruskal();
};


#endif
