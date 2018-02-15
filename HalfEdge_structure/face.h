#ifndef FACE_H
#define FACE_H

#include "halfedge.h"

class HalfEdge;

class Face
{
protected:
    static int NB_FACES;
protected:
    int _id;
    HalfEdge* _halfEdge;
    int _nbVertices;

public:
    Face();
    Face(HalfEdge* halfEdge);


    // Getters
    int getId(){ return _id; }
    HalfEdge* getHalfEdge(){ return _halfEdge; }
    int getNbVertices(){ return _nbVertices; }

    // Setters
    void setHalfEdge(HalfEdge* he){ _halfEdge = he; }
    void setNbVertices(const int nb){ _nbVertices = nb; }

    // Other functions
    void display();
};

#endif // FACE_H
