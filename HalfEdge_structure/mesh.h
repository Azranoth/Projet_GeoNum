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

struct classComp
{
    bool operator() (const int& id1, const int& id2) const
    { return id1<id2; }
};

struct classComp2
{
    bool operator() (const std::pair<int, int>& id1, const std::pair<int, int>& id2) const
    { return (id1.first<id2.first) || ((id1.first == id2.first) && (id1.second < id2.second)); }
};

class Mesh
{
protected:
    std::map<int, Vertex*, classComp> _vertices;
    std::map<int, Face*, classComp> _faces;
    std::map<std::pair<int, int>, HalfEdge*, classComp2> _edges;

public:
    Mesh();
    Mesh(std::map<int, Vertex*, classComp> vertices);
    Mesh(std::map<int, Face*, classComp> faces);
    Mesh(std::map<int, Vertex*, classComp> vertices, std::map<int, Face*, classComp> faces);

    // Getters
    std::map<int, Vertex*, classComp> getVertices(){ return _vertices; }
    std::map<int, Face*, classComp> getFaces(){ return _faces; }

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
