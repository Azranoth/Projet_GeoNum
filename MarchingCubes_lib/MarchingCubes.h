
#ifndef MARCHING_CUBES_H
#define MARCHING_CUBES_H


class VoxelGrid;


#include "VoxelGrid.h"
#include <array>

using namespace Eigen;


typedef std::array<int,3> Triangle;
typedef std::array<double,3> CoordsKey;

class MarchingCubes {

protected:
    VoxelGrid* _voxelGrid;
    std::map<CoordsKey, Vertex*> _listOfVertices;
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
