#include "VoxelGrid.h"


VoxelGrid::VoxelGrid()
{

}


VoxelGrid::VoxelGrid(std::vector<Plane*> planes, double cubeSize, double density, double noise)
{
    // Control values
    double minX = 0.0;
    double maxX = 0.0;
    double minY = 0.0;
    double maxY = 0.0;
    double minZ = 0.0;
    double maxZ = 0.0;

    std::vector<Vertex*> planesCenter;
    std::map<int, Plane*, classComp> planes_map;

    // Retrieve planes center and store planes in a map to speed up plane search
    for(auto it = planes.begin(); it != planes.end(); ++it)
    {
        planesCenter.push_back((*it)->center());
        planes_map[(*it)->center()->getId()] = *it;
    }

    // Get minimum x value
    std::sort(planesCenter.begin(), planesCenter.end(), classCompOnX());
    minX = planesCenter[0]->x();
    maxX = planesCenter[planesCenter.size()-1]->x();

    // Get maximum y value
    std::sort(planesCenter.begin(), planesCenter.end(), classCompOnY());
    minY = planesCenter[0]->y();
    maxY = planesCenter[planesCenter.size()-1]->y();

    // Get minimum z value
    std::sort(planesCenter.begin(), planesCenter.end(), classCompOnZ());
    minZ = planesCenter[0]->z();
    maxZ = planesCenter[planesCenter.size()-1]->z();

    // Initialize kdTree
    kDTree planesTree;
    planesTree.init(planesCenter);

    // Start grid creation

    //this->firstCell = new

    //while()



}


// Auxiliary methods


double VoxelGrid::euclideanDistance(Eigen::Vector3d p1, Eigen::Vector3d p2)
{
    return std::sqrt( std::pow(p2(0) - p1(0), 2) + std::pow(p2(1) - p1(1), 2) + std::pow(p2(2) - p1(2), 2));
}


bool VoxelGrid::computeCellPointValue(Plane* nearestPlane, Eigen::Vector3d point, double* val)
{
    Vertex* planeCenter = nearestPlane->center();
    Eigen::Vector3d pointProjectedOnPlane = point - Eigen::Vector3d(planeCenter->x(), planeCenter->y(), planeCenter->z());
    
    // Verify if value's validity
    if(euclideanDistance(point, Eigen::Vector3d(planeCenter->x(), planeCenter->y(), planeCenter->z())) < this->maxDistanceValue)
    {
        *val = pointProjectedOnPlane.dot(nearestPlane->normal());
        return true;
    }
    else
    {
        return false;
    }
}


gridCell* VoxelGrid::newCell(Plane* nearestPlane, double x0, double y0, double z0)
{
    double p0Value = 0.0;
    double p1Value = 0.0;
    double p2Value = 0.0;
    double p3Value = 0.0;
    double p4Value = 0.0;
    double p5Value = 0.0;
    double p6Value = 0.0;
    double p7Value = 0.0;

    std::map<cellKey, cellPoint*>::iterator cellIt;
    std::array<double, 3> keys = {0.0, 0.0, 0.0};
    Eigen::Vector3d PositionP0(x0, y0, z0);
    Eigen::Vector3d positionP1 = PositionP0 + Eigen::Vector3d(this->cubeSize, 0.0, 0.0);
    Eigen::Vector3d positionP2 = PositionP0 + Eigen::Vector3d(this->cubeSize, 0.0, this->cubeSize);
    Eigen::Vector3d positionP3 = PositionP0 + Eigen::Vector3d(0.0, 0.0, this->cubeSize);
    Eigen::Vector3d positionP4 = PositionP0 + Eigen::Vector3d(0.0, -this->cubeSize, 0.0);
    Eigen::Vector3d positionP5 = PositionP0 + Eigen::Vector3d(this->cubeSize, -this->cubeSize, 0.0);
    Eigen::Vector3d positionP6 = PositionP0 + Eigen::Vector3d(this->cubeSize, -this->cubeSize, this->cubeSize);
    Eigen::Vector3d positionP7 = PositionP0 + Eigen::Vector3d(0.0, -this->cubeSize, this->cubeSize);
    gridCell* newCell = new gridCell();

    // Verify cube validity
        // P0
    if(computeCellPointValue(nearestPlane, PositionP0, &p0Value) > this->maxDistanceValue)
    {
        return nullptr;
    }
        // P1
    if(computeCellPointValue(nearestPlane, positionP1, &p1Value) > this->maxDistanceValue)
    {
        return nullptr;
    }
        // P2
    if(computeCellPointValue(nearestPlane, positionP2, &p2Value) > this->maxDistanceValue)
    {
        return nullptr;
    }
        // P3
    if(computeCellPointValue(nearestPlane, positionP3, &p3Value) > this->maxDistanceValue)
    {
        return nullptr;
    }
        // P4
    if(computeCellPointValue(nearestPlane, positionP4, &p4Value) > this->maxDistanceValue)
    {
        return nullptr;
    }
        // P5
    if(computeCellPointValue(nearestPlane, positionP5, &p5Value) > this->maxDistanceValue)
    {
        return nullptr;
    }
        // P6
    if(computeCellPointValue(nearestPlane, positionP6, &p6Value) > this->maxDistanceValue)
    {
        return nullptr;
    }
        // P7
    if(computeCellPointValue(nearestPlane, positionP7, &p7Value) > this->maxDistanceValue)
    {
        return nullptr;
    }

    // P0
    keys[0] = PositionP0(0);
    keys[1] = PositionP0(1);
    keys[2] = PositionP0(2);
    if((cellIt = this->cellpoints.find(keys)) == this->cellpoints.end())
    {
        newCell->points[0] = new cellPoint(PositionP0, p0Value);
        this->cellpoints[keys] = newCell->points[0];
    }
    else
    {
        newCell->points[0] = cellIt->second;
    }

    // P1
    keys[0] = positionP1(0);
    keys[1] = positionP1(1);
    keys[2] = positionP1(2);
    if((cellIt = this->cellpoints.find(keys)) == this->cellpoints.end())
    {
        newCell->points[1] = new cellPoint(positionP1, p1Value);
        this->cellpoints[keys] = newCell->points[1];
    }
    else
    {
        newCell->points[1] = cellIt->second;
    }

    // P2
    keys[0] = positionP2(0);
    keys[1] = positionP2(1);
    keys[2] = positionP2(2);
    if((cellIt = this->cellpoints.find(keys)) == this->cellpoints.end())
    {
        newCell->points[2] = new cellPoint(positionP2, p2Value);
        this->cellpoints[keys] = newCell->points[2];
    }
    else
    {
        newCell->points[2] = cellIt->second;
    }

    // P3
    keys[0] = positionP3(0);
    keys[1] = positionP3(1);
    keys[2] = positionP3(2);
    if((cellIt = this->cellpoints.find(keys)) == this->cellpoints.end())
    {
        newCell->points[3] = new cellPoint(positionP3, p3Value);
        this->cellpoints[keys] = newCell->points[3];
    }
    else
    {
        newCell->points[3] = cellIt->second;
    }

    // P4
    keys[0] = positionP4(0);
    keys[1] = positionP4(1);
    keys[2] = positionP4(2);
    if((cellIt = this->cellpoints.find(keys)) == this->cellpoints.end())
    {
        newCell->points[4] = new cellPoint(positionP4, p4Value);
        this->cellpoints[keys] = newCell->points[4];
    }
    else
    {
        newCell->points[4] = cellIt->second;
    }

    // P5
    keys[0] = positionP5(0);
    keys[1] = positionP5(1);
    keys[2] = positionP5(2);
    if((cellIt = this->cellpoints.find(keys)) == this->cellpoints.end())
    {
        newCell->points[5] = new cellPoint(positionP5, p5Value);
        this->cellpoints[keys] = newCell->points[5];
    }
    else
    {
        newCell->points[5] = cellIt->second;
    }

    // P6
    keys[0] = positionP6(0);
    keys[1] = positionP6(1);
    keys[2] = positionP6(2);
    if((cellIt = this->cellpoints.find(keys)) == this->cellpoints.end())
    {
        newCell->points[6] = new cellPoint(positionP6, p6Value);
        this->cellpoints[keys] = newCell->points[6];
    }
    else
    {
        newCell->points[6] = cellIt->second;
    }

    // P7
    keys[0] = positionP7(0);
    keys[1] = positionP7(1);
    keys[2] = positionP7(2);
    if((cellIt = this->cellpoints.find(keys)) == this->cellpoints.end())
    {
        newCell->points[7] = new cellPoint(positionP7, p7Value);
        this->cellpoints[keys] = newCell->points[7];
    }
    else
    {
        newCell->points[7] = cellIt->second;
    }

    return newCell;
}
