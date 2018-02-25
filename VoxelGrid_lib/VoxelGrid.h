#ifndef __VOXELGRID_H
#define __VOXELGRID_H

#include <../Eigen/Eigen/Dense>

#include "mesh.h"
#include "PlanesGraph.h"

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


struct gridCell
{
    cellPoint* points[8];
    gridCell* nextCell;

    gridCell();
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

    // Create a kd-tree with with planes centroid for nearest plane search
    // pour chaque point P0 chercher le plan le plus proche via le kd-tree
    VoxelGrid(std::vector<Plane *> planes, double cubeSize, double density, double noise);

// Auxiliary methods
private:


    /**
     * @brief euclideanDistance compute euclidean distance between two points
     * @param p1
     * @param p2
     * @return
     */
    double euclideanDistance(Eigen::Vector3d p1, Eigen::Vector3d p2);


    /**
     * @brief computeCellPointValue compute the signed distance with the nearest plane centroid and store the result in the pointer val. Return false if the value is undefined (i.e : if the signed distance is greater than P + delta
     * @param val
     * @return
     */
    bool computeCellPointValue(Plane* nearestPlane, Eigen::Vector3d point, double* val);

    /**
     * @brief newCell create the cell with the given P0 point
     * @param x0
     * @param y0
     * @param z0
     * @return
     */
    gridCell* newCell(Plane *nearestPlane, double x0, double y0, double z0);

// Methods
public:

    gridCell* getFirstCell();
};



#endif
