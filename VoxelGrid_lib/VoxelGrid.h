#ifndef __VOXELGRID_H
#define __VOXELGRID_H

#include <../Eigen/Eigen/Dense>

#include "mesh.h"
#include "PlanesGraph.h"

struct cellPoint
{
    Eigen::VectorXd position;
    double value;

public:
    cellPoint() {}

    cellPoint(Eigen::VectorXd pos, double val)
    {
        this->position = pos;
        this->value = val;
    }
};


struct gridCell
{
    cellPoint* points[8];
    gridCell* nextCell;
};


class VoxelGrid
{
// Attributes
private:
    gridCell* firstCell;

// Constructors and destructor
public:

    VoxelGrid();

    // Create a kd-tree with with planes centroid for nearest plane search
    // pour chaque point P0 chercher le plan le plus proche via le kd-tree
    VoxelGrid(PlanesGraph* planes);


// Methods
public:

    gridCell* getFirstCell();
};



#endif
