
#include "Edge.h"

Edge::Edge(){
    this->_destPlane = NULL;
    this->_srcPlane = NULL;
    this->_edgeWeight = -1.;
}

Edge::Edge(Node *src, Node *target, double weight){
    this->_srcPlane = src;
    this->_destPlane = target;
    this->_edgeWeight = weight;
}

Edge::Edge(Node *src, Node *target){
    this->_srcPlane = src;
    this->_destPlane = target;
    this->_edgeWeight = -1.;
}

Edge::Edge(Node* target, double weight){
    this->_srcPlane = NULL;
    this->_destPlane = target;
    this->_edgeWeight = weight;
}

Edge::Edge(Node* target){
    this->_srcPlane = NULL;
    this->_destPlane = target;
    this->_edgeWeight = -1.;
}

Edge::Edge(double weight){
    this->_srcPlane = NULL;
    this->_destPlane = NULL;
    this->_edgeWeight = weight;
}

void Edge::display(){
    std::cout << "Edge " << this->_srcPlane->getCenter()->getId() << " <----> " << this->_destPlane->getCenter()->getId() /*<< " of weight " << this->_edgeWeight*/ << std::endl;
}
