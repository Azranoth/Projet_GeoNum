#ifndef MESH_H
#define MESH_H

#include <map>
#include <string>
#include <fstream>
#include <sstream>

#include "vertex.h"
#include "face.h"

class Vertex;
class Face;

class Mesh
{
protected:
    std::map<int, Vertex*> _vertices;
    std::map<int, Face*> _faces;
    std::map<std::pair<int, int>, HalfEdge*> _edges;

public:
    Mesh();
    Mesh(std::map<int, Vertex*> vertices);
    Mesh(std::map<int, Face*> faces);
    Mesh(std::map<int, Vertex*> vertices, std::map<int, Face*> faces);

    // Getters
    std::map<int, Vertex*> getVertices(){ return _vertices; }
    std::map<int, Face*> getFaces(){ return _faces; }

    // Other functions
    void addVertex(Vertex* v);
    void addFace(Face* f);
    void addEdge(HalfEdge* he);
    void display();
    void verticesDisplay();
    void importOFF(const char* filename);
    void exportOFF(const char* filename);

};

#endif // MESH_H
