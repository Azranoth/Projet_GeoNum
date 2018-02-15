

#include "Node.h"


Node::Node(){
    this->_planeCenter  = NULL;
    this->_normalVector = Vector3d::Zero();
    this->_listOfEdges  = std::map<int, Edge*, classCompEdges>();
}

Node::Node(Vector3d normalVector, Vertex* center, std::map<int, Edge*, classCompEdges> map){
    this->_planeCenter  = center;
    this->_normalVector = normalVector;
    this->_listOfEdges  = map;
}

Node::Node(Vector3d normalVector, Vertex* center){
    this->_planeCenter  = center;
    this->_normalVector = normalVector;
    this->_listOfEdges  = std::map<int, Edge*, classCompEdges>();
}

Node::Node(Vector3d normalVector){
    this->_planeCenter  = NULL;
    this->_normalVector = normalVector;
    this->_listOfEdges  = std::map<int, Edge*, classCompEdges>();
}

Node::Node(Vertex* center){
    this->_planeCenter  = center;
    this->_normalVector = Vector3d::Zero();
    this->_listOfEdges  = std::map<int, Edge*, classCompEdges>();
}

void Node::display(){
    std::cout << "Node of center " << this->_planeCenter->getId() /*<< ", of normal " << this->_normalVector*/ << " with edges : " << std::endl;
    std::map<int, Edge*, classCompEdges>::iterator itE;
    for(itE = this->_listOfEdges.begin(); itE != this->_listOfEdges.end(); ++itE){
        std::cout << "--------";
        (*itE).second->display();
    }
}

void Node::addEdge(Node *n){
    if(this->_listOfEdges.find(n->getCenter()->getId()) == this->_listOfEdges.end()){
        Edge* newE = new Edge(this->_planeCenter, n->getCenter());
        double weight = 1 - (  this->_planeCenter->x() * n->getCenter()->x()
                             + this->_planeCenter->y() * n->getCenter()->y()
                             + this->_planeCenter->z() * n->getCenter()->z());
        newE->setEdgeWeight(weight);
        this->_listOfEdges.insert(std::make_pair(n->getCenter()->getId(), newE));
    }
}

void Node::addEdge(Node *n, double weight){
    if(this->_listOfEdges.find(n->getCenter()->getId()) == this->_listOfEdges.end()){
        Edge* newE = new Edge(this->_planeCenter, n->getCenter());
        newE->setEdgeWeight(weight);
        this->_listOfEdges.insert(std::make_pair(n->getCenter()->getId(), newE));
    }
}

