#include "halfedge.h"

HalfEdge::HalfEdge()
{
    this->_sourceVertex = NULL;
    this->_face = NULL;
    this->_nextHalfEdge = NULL;
    this->_previousHalfEdge = NULL;
    this->_teteBeche = NULL;
}

HalfEdge::HalfEdge(Vertex* sourceVertex)
{
    this->_sourceVertex = sourceVertex;
    this->_face = NULL;
    this->_nextHalfEdge = NULL;
    this->_previousHalfEdge = NULL;
    this->_teteBeche = NULL;
}

HalfEdge::HalfEdge(Vertex* sourceVertex, Face* face, HalfEdge* nextHalfEdge, HalfEdge* previousHalfEdge, HalfEdge* teteBeche)
{
    this->_sourceVertex = sourceVertex;
    this->_face = face;
    this->_nextHalfEdge = nextHalfEdge;
    this->_previousHalfEdge = previousHalfEdge;
    this->_teteBeche = teteBeche;
}

void HalfEdge::display(){
    std::cout << "HalfEdge from source vertex " << this->_sourceVertex->getId() << " belonging to face " << this->_face->getId() << " and pointing to vertex " << this->_teteBeche->getSourceVertex()->getId() << " which is pointing on " << this->_teteBeche->getNextHalfEdge()->getSourceVertex()->getId() << std::endl;
}
