
#ifndef MARCHING_CUBES_H
#define MARCHING_CUBES_H


class VoxelGrid;


#include "VoxelGrid.h"
#include <array>

using namespace Eigen;

/**
 * @brief Triangle  Type representing a triangle using the identifiers of the 3 vertices composing it
 */
typedef std::array<int,3> Triangle;

/**
 * @brief CoordsKey Type used as key for the map of vertices : vertices are stored using their coordinates as key
 */
typedef std::array<double,3> CoordsKey;


/**
 * @brief The MarchingCubes class    Allows the application of the marching cubes algorithm on a voxel grid
 */
class MarchingCubes {

protected:
    VoxelGrid* _voxelGrid;                          // The voxel grid
    std::map<CoordsKey, Vertex*> _listOfVertices;   // List of vertices created by the Marching Cubes algorithm
    std::vector<Triangle> _listOfTriangles;         // List of faces created by the Marching Cubes algorithm


public:
    //Constructors
    MarchingCubes();
    MarchingCubes(VoxelGrid* grid);

    // Other methods

    /**
     * @brief clearMapAndVector Clean the lists of vertices & triangles of the MarchingCubes object
     */
    void clearMapAndVector();

    /**
     * @brief polygonization    Apply the Marching Cubes algorithm on the voxel grid, filling the lists of vertices & triangles of the MarchingCubes object
     */
    void polygonization();

    /**
     * @brief VertexInterp      Interpolate the coordinates an the intersection point according to the edge's vertices (p1, p2) & their respective value (valp1, valp2), then return a Vertex object
     * @param p1
     * @param p2
     * @param valp1
     * @param valp2
     * @return
     */
    Vertex* VertexInterp(Vector3d p1, Vector3d p2, double valp1, double valp2);

    /**
     * @brief exportToOFFFile   Export the result of the Marching Cubes algorithm (i.e the lists of vertices & triangles) to an OFF file of filepath filename.
     * @param filename
     */
    void exportToOFFFile(const char *filename);
};


#endif
