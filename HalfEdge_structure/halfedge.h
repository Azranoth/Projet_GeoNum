#ifndef HALFEDGE_H
#define HALFEDGE_H

#include "vertex.h"
#include "face.h"

class Vertex;
class Face;

class HalfEdge
{
protected:
    Vertex* _sourceVertex;
    Face* _face;
    HalfEdge* _nextHalfEdge;     // In _face
    HalfEdge* _previousHalfEdge; // In _face
    HalfEdge* _teteBeche;

public:
    HalfEdge();

    HalfEdge(Vertex* sourceVertex);

    HalfEdge(Vertex* sourceVertex, Face* face, HalfEdge* nextHalfEdge, HalfEdge* previousHalfEdge, HalfEdge* teteBeche);

    // Getters
    Vertex* getSourceVertex()  { return _sourceVertex; }
    Face* getFace()            { return _face; }
    HalfEdge* getNextHalfEdge(){ return _nextHalfEdge; }
    HalfEdge* getPrevHalfEdge(){ return _previousHalfEdge; }
    HalfEdge* getTeteBeche()   { return _teteBeche; }

    // Setters
    void setSourceVertex(Vertex* v)   { _sourceVertex = v; }
    void setFace(Face* f)             { _face = f; }
    void setNextHalfEdge(HalfEdge* he){ _nextHalfEdge = he; }
    void setPrevHalfEdge(HalfEdge* he){ _previousHalfEdge = he; }
    void setTeteBeche(HalfEdge* he)   { _teteBeche = he; }

    // Other functions
    void display();
};

#endif // HALFEDGE_H
