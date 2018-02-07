#include "face.h"

int Face::NB_FACES = 0;

Face::Face()
{
    this->_id = Face::NB_FACES++;
    this->_halfEdge = NULL;
    this->_nbVertices = 0;
}

Face::Face(HalfEdge* halfEdge)
{
    this->_id = Face::NB_FACES++;
    this->_halfEdge = halfEdge;
    this->_nbVertices = 0;
}

void Face::display(){

    HalfEdge* temp = this->_halfEdge;
    std::cout << "------FACE OF ID " << this->_id << " : " << std::endl;
    temp->display();
    temp = temp->getNextHalfEdge();
    while(temp != this->_halfEdge){
        temp->display();
        temp = temp->getNextHalfEdge();
    }
}

