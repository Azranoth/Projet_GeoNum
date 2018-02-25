

#include "Node.h"


// ----- Constructors
Node::Node(){
    this->_plane = new Plane(nullptr, Vector3d(0,0,0));
    this->_listOfEdges  = std::map<int, Edge*, classCompEdges>();
    this->_edgesToThis  = std::map<int, Edge*, classCompEdges>();
    this->_alreadyOriented = false;
}

Node::Node(Vector3d normalVector, Vertex* center, std::map<int, Edge*, classCompEdges> map){
    this->_plane = new Plane(center, normalVector);
    this->_listOfEdges  = map;
    this->_edgesToThis  = std::map<int, Edge*, classCompEdges>();
    this->_alreadyOriented = false;
}

Node::Node(Vector3d normalVector, Vertex* center){
    this->_plane = new Plane(center, normalVector);
    this->_listOfEdges  = std::map<int, Edge*, classCompEdges>();
    this->_edgesToThis  = std::map<int, Edge*, classCompEdges>();
    this->_alreadyOriented = false;
}

Node::Node(Vector3d normalVector){
    this->_plane = new Plane(nullptr, normalVector);
    this->_listOfEdges  = std::map<int, Edge*, classCompEdges>();
    this->_edgesToThis  = std::map<int, Edge*, classCompEdges>();
    this->_alreadyOriented = false;
}

Node::Node(Vertex* center){
    this->_plane = new Plane(center, Vector3d(0,0,0));
    this->_listOfEdges  = std::map<int, Edge*, classCompEdges>();
    this->_edgesToThis  = std::map<int, Edge*, classCompEdges>();
    this->_alreadyOriented = false;
}


// ----- Methods
void Node::display(){
    std::cout << "Node of center " << this->_plane->center()->getId() << std::endl
              << "----- of center (" << this->_plane->center()->x() << ", " << this->_plane->center()->y() << ", " << this->_plane->center()->z() << ")" << std::endl
              << "----- of normal " << this->_plane->normal()<< std::endl
              << "----- Edges taking source in this point : " << std::endl;
    std::map<int, Edge*, classCompEdges>::iterator itE;
    for(itE = this->_listOfEdges.begin(); itE != this->_listOfEdges.end(); ++itE){
        std::cout << "---------- ";
        (*itE).second->display();
    }
    std::cout << "----- Edges pointing to this point : " << std::endl;
    for(itE = this->_edgesToThis.begin(); itE != this->_edgesToThis.end(); ++itE){
        std::cout << "---------- ";
        (*itE).second->display();
    }
}

void Node::addEdge(Node *n){
    if(this->_listOfEdges.find(n->getCenter()->getId()) == this->_listOfEdges.end()){
        Edge* newE = new Edge(this, n);
        double weight = 1 - (  this->_plane->center()->x() * n->getCenter()->x()
                             + this->_plane->center()->y() * n->getCenter()->y()
                             + this->_plane->center()->z() * n->getCenter()->z());
        newE->setEdgeWeight(weight);
        this->_listOfEdges.insert(std::make_pair(n->getCenter()->getId(), newE));
    }
}


void Node::addEdge(Node *n, double weight){
    if(this->_listOfEdges.find(n->getCenter()->getId()) == this->_listOfEdges.end()){
        Edge* newE = new Edge(this, n);
        newE->setEdgeWeight(weight);
        this->_listOfEdges.insert(std::make_pair(n->getCenter()->getId(), newE));
    }
}


void Node::addEdgePointingToThisPlane(Node* src){
        Edge* newE = new Edge(src, this);
        double weight = 1 - (  this->_plane->center()->x() * src->getCenter()->x()
                             + this->_plane->center()->y() * src->getCenter()->y()
                             + this->_plane->center()->z() * src->getCenter()->z());
        newE->setEdgeWeight(weight);
        this->_edgesToThis.insert(std::make_pair(src->getCenter()->getId(), newE));
}


void Node::addEdgePointingToThisPlane(Node* src, double weight){
        Edge* newE = new Edge(src, this);
        newE->setEdgeWeight(weight);
        this->_edgesToThis.insert(std::make_pair(src->getCenter()->getId(), newE));
}



void Node::orientNormalsMap(std::map<int, Node*, classCompNodes> map, int parentCalling){
    ///std::cout << "Orientation of plane " << this->getCenter()->getId() << std::endl;

    if(!this->_alreadyOriented || parentCalling == -1){
        ///if(parentCalling == -1)
            ///std::cout << "----- First call" << std::endl;
        ///std::cout << "----- Has not been oriented yet. " << this->_listOfEdges.size() << " edges taking source in this point --- " << this->_edgesToThis.size() << " edges pointing to this point" << std::endl;
        this->isOriented();

        std::map<int, Edge*, classCompEdges>::iterator itETar;
        Node* temp;

        for(itETar = this->_listOfEdges.begin(); itETar != this->_listOfEdges.end(); ++itETar){
            ///std::cout << "----- Target plane " << (*itETar).second->getTargetPlane()->getCenter()->getId() << std::endl;

            // For each next plane that has not been oriented yet
            if( (*itETar).second->getTargetPlane()->getCenter()->getId() != parentCalling && !(*itETar).second->getTargetPlane()->isOriented() ){
                ///std::cout << "---------- Dot result : " << this->_plane->normal().dot( (*itETar).second->getTargetPlane()->getNormal()) << std::endl;


                // Invert next plane's normal if the scalar product of its normal and this plane's normal is negative
                if( this->_plane->normal().dot( (*itETar).second->getTargetPlane()->getNormal() ) < 0 ) {

                    temp = (*map.find((*itETar).second->getTargetPlane()->getCenter()->getId())).second;
                    temp->setNormal(-(*itETar).second->getTargetPlane()->getNormal() );
                    ///std::cout << "--------------- Normal inversion done." << std::endl;
                }
                ///std::cout << "positive dot" << std::endl;
                map[(*itETar).second->getTargetPlane()->getCenter()->getId()]->orientNormalsMap(map, this->getCenter()->getId());
            }
        }
        std::map<int, Edge*, classCompEdges>::iterator itESrc;
        for(itESrc = this->_edgesToThis.begin(); itESrc != this->_edgesToThis.end(); ++itESrc){
            ///std::cout << "----- Source plane " << (*itESrc).second->getSrcPlane()->getCenter()->getId() << std::endl;

            // For each next plane that has not been oriented yet
            if(  (*itESrc).second->getSrcPlane()->getCenter()->getId() != parentCalling &&!(*itESrc).second->getSrcPlane()->isOriented() ){
                ///std::cout << "---------- Dot result : " <<  "   " << this->_plane->normal().dot( (*itESrc).second->getSrcPlane()->getNormal()) << std::endl;

                // Invert next plane's normal if the scalar product of its normal and this plane's normal is negative
                if( this->_plane->normal().dot( (*itESrc).second->getSrcPlane()->getNormal() ) < 0 ) {

                    temp = (*map.find((*itESrc).second->getSrcPlane()->getCenter()->getId())).second;
                    temp->setNormal(-(*itESrc).second->getSrcPlane()->getNormal() );
                    ///std::cout << "--------------- Normal inversion done." << std::endl;
                }
                ///std::cout << "positive dot" << std::endl;
                map[(*itESrc).second->getSrcPlane()->getCenter()->getId()]->orientNormalsMap(map, this->getCenter()->getId());
            }
        }
    }
    else{
        std::cout << "has been oriented" << std::endl;
    }
}

