
#ifndef MARCHING_CUBES_H
#define MARCHING_CUBES_H


class VoxelGrid;


#include "VoxelGrid.h"
#include <array>

using namespace Eigen;



struct classCompVertices
{
    bool operator() (const int& id1, const int& id2) const
    { return id1<id2; }
};

typedef std::array<int,3> Triangle;

class MarchingCubes {

protected:
    VoxelGrid* _voxelGrid;
    std::map<int, Vertex*, classCompVertices> _listOfVertices;
    std::vector<Triangle> _listOfTriangles;


public:
    MarchingCubes();
    MarchingCubes(VoxelGrid* grid);

    void clearMapAndVector();
    void polygonization();
    Vertex* VertexInterp(Vector3d p1, Vector3d p2, double valp1, double valp2);
    void exportToOFFFile(const char *filename);
};


#endif
