#ifndef __VOXELGRID_H
#define __VOXELGRID_H

#include <../Eigen/Eigen/Dense>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "mesh.h"
#include "kDTree.h"
#include "PlanesGraph.h"

/**
 * @brief The cellPoint struct is the representation of the grid's cell. Each cell has a position and the value of the signed distance
 */
struct cellPoint
{
    Eigen::Vector3d position;
    double value;

public:
    cellPoint() {}

    cellPoint(Eigen::Vector3d pos, double val)
    {
        this->position = pos;
        this->value = val;
    }
};


/**
 * @brief The gridCell struct is the representation of a cube used by the marching cubes algorithm
 */
struct gridCell
{
    cellPoint* points[8];
    gridCell* nextCell;

    gridCell() {}
};

typedef std::array<double, 3> cellKey;


class VoxelGrid
{
// Attributes
private:
    gridCell* firstCell;
    double maxDistanceValue;
    double cubeSize;
    std::map<cellKey, cellPoint*> cellpoints;


// Constructors and destructor
public:

    VoxelGrid();

    /**
     * @brief VoxelGrid create the voxels grid
     * @param planes
     * @param cubeSize
     * @param density
     * @param noise
     */
    VoxelGrid(std::vector<Plane *> planes, double cubeSize, double density, double noise);

// Auxiliary methods
private:


    /**
     * @brief setPointValues compute data needed for point construction. Store new coordinates in pointers x, y and z
     * @param x
     * @param y
     * @param z
     * @param planes_map std::map container with planes. Used to speed up the nearest plane search
     * @return
     */
    Plane* getnearestPlane(double x, double y, double z, Vertex *planeCenter, std::map<int, Plane *, classComp> &planes_map, kDTree &planesTree);


    /**
     * @brief Hausdorff compute Hausdorff distance between the projection of the point p1 in the nearest plane with the nearest planes center
     * @param p1
     * @param nearestPlaneCenter centroid of the nearest plane
     * @param planeNormal
     * @param planesTree
     * @return
     */
    double Hausdorff(Eigen::Vector3d p1, Eigen::Vector3d nearestPlaneCenter, Eigen::Vector3d planeNormal, kDTree& planesTree);


    /**
     * @brief computeCellPointValue compute the signed distance with the nearest plane centroid and store the result in the pointer val. Return false if the value is undefined (i.e : if the Hausdorff distance is greater than P + delta
     * @param planesTree kDTree for planes center
     * @param planes_map
     * @param point
     * @param val
     * @return
     */
    bool computeCellPointValue(kDTree& planesTree, std::map<int, Plane*, classComp>& planes_map, Eigen::Vector3d point, double* val);

    /**
     * @brief newCell create the 8 points of the cell with the given P0. Each point is stored in a map to reduce the memory complexity
     * @param planesTree
     * @param planes_map
     * @param x0
     * @param y0
     * @param z0
     * @return
     */
    gridCell* newCell(kDTree& planesTree, std::map<int, Plane*, classComp>& planes_map, double x0, double y0, double z0);

// Methods
public:

    /**
     * @brief getFirstCell return the first cell of the grid
     * @return
     */
    gridCell* getFirstCell();


    /**
     * @brief toString Return the string version of the grid
     * @return
     */
    std::string toString();
};

inline std::ostream& operator<<(std::ostream& os, VoxelGrid& obj)
{
    os << obj.toString();

    return os;
}


#endif
