
#include "Edge.h"

Edge::Edge(){
    this->_centerOfDestPlane = NULL;
    this->_centerofSrcPlane = NULL;
    this->_edgeWeight = -1.;
}

Edge::Edge(Vertex *src, Vertex *target, double weight){
    this->_centerofSrcPlane = src;
    this->_centerOfDestPlane = target;
    this->_edgeWeight = weight;
}

Edge::Edge(Vertex *src, Vertex *target){
    this->_centerofSrcPlane = src;
    this->_centerOfDestPlane = target;
    this->_edgeWeight = -1.;
}

Edge::Edge(Vertex* target, double weight){
    this->_centerofSrcPlane = NULL;
    this->_centerOfDestPlane = target;
    this->_edgeWeight = weight;
}

Edge::Edge(Vertex* target){
    this->_centerofSrcPlane = NULL;
    this->_centerOfDestPlane = target;
    this->_edgeWeight = -1.;
}

Edge::Edge(double weight){
    this->_centerofSrcPlane = NULL;
    this->_centerOfDestPlane = NULL;
    this->_edgeWeight = -weight;
}

void Edge::display(){
    std::cout << "Edge " << this->_centerofSrcPlane->getId() << " <----> " << this->_centerOfDestPlane->getId() /*<< " of weight " << this->_edgeWeight*/ << std::endl;
}
