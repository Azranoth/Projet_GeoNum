#include "VoxelGrid.h"


VoxelGrid::VoxelGrid()
{
    this->firstCell = nullptr;
}


VoxelGrid::VoxelGrid(std::vector<Plane*> planes, double cubeSize, double density, double noise)
{
    int i = 0;
    // Control values
    double minX = 0.0;
    double maxX = 0.0;
    double minY = 0.0;
    double maxY = 0.0;
    double minZ = 0.0;
    double maxZ = 0.0;

    // Used to speed up neigbors searches
    kDTree planesTree;

    // Used to retrieve planes data
    std::vector<Vertex*> planesCenter;
    std::map<int, Plane*, classComp> planes_map;

    // Used for grid construction
    bool isFirstCellOfRow = false;
    bool isFirstCellOfPlane = false;
    bool isFirstCellFound = false;
    Eigen::Vector3d firstCellOfRow;     // First cell of each row of the grid
    Eigen::Vector3d firstCellOfPlane;   // First cell of each 2 dimensionnal table of the grid
    gridCell* lastCell = nullptr;
    gridCell* currentCell = nullptr;
    double currentCellX = 0.0;
    double currentCellY = 0.0;
    double currentCellZ = 0.0;

    this->cubeSize = cubeSize;
    this->maxDistanceValue = density + noise;

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

    // Initialize kdTrees
    planesTree.init(planesCenter);

    // Start grid creation

    // Retrieve first point coordinates
    currentCellX = minX-this->maxDistanceValue+0.1;
    currentCellY = maxY+this->maxDistanceValue-0.1;
    currentCellZ = minZ-this->maxDistanceValue+0.1;

    std::cout << "maxX : " << maxX << ", minX : " << minX << ", maxY : " << maxY << ", minY : " << minY << ", maxZ : " << maxZ << " and minZ : " << minZ << std::endl;
    std::cout << "cellX : " << currentCellX << ", cellY : " << currentCellY << " and cellZ : " << currentCellZ << std::endl;
    std::cout << "cubeSize : " << this->cubeSize << ", " << this->maxDistanceValue << std::endl;

    isFirstCellOfPlane = true;
    isFirstCellOfRow = true;

    // Build the grid

    // Z variation
    while( (currentCellZ<maxZ) || ( (currentCellZ>=maxZ) && (currentCell != nullptr) ) )
    {
        // Y Variation
        while( (currentCellY>minY) || ( (currentCellY>minY-this->maxDistanceValue) && (currentCell != nullptr) ) )
        {
            // X variation
            while( (currentCellX<maxX) || ( (currentCellZ>=maxX) && (currentCell != nullptr) ) )
            {
//                std::cout << "cellX : " << currentCellX << ", cellY : " << currentCellY << " and cellZ : " << currentCellZ << std::endl;

                // Create the cell
                currentCell = newCell(planesTree, planes_map, currentCellX, currentCellY, currentCellZ);
                i++;

                // Keep the first cell of the row to create the next row
                if(isFirstCellOfRow)
                {
                    isFirstCellOfRow = false;
                    firstCellOfRow(0) = currentCellX;
                    firstCellOfRow(1) = currentCellY - this->cubeSize;
                    firstCellOfRow(2) = currentCellZ;
                }

                // Keep the first cell of the plane to create the next one
                if(isFirstCellOfPlane)
                {
                    isFirstCellOfPlane = false;
                    firstCellOfPlane(0) = currentCellX;
                    firstCellOfPlane(1) = currentCellY;
                    firstCellOfPlane(2) = currentCellZ + this->cubeSize;
                }

                // Add current cell as lastCell->next if current cell is valid
                if(currentCell != nullptr)
                {
                    // One cell to rull them all
                    // We must find the first cell to initialize the chained list
                    if(!isFirstCellFound)
                    {
                        isFirstCellFound = true;
                        this->firstCell = currentCell;
                        lastCell = currentCell;
                    }
                    else
                    {
                        lastCell->nextCell = currentCell;
                        lastCell = currentCell;
                    }
                }

                currentCellX += this->cubeSize;
            }
            currentCellX = firstCellOfRow(0);
            currentCellY = firstCellOfRow(1);
            currentCellZ = firstCellOfRow(2);
            isFirstCellOfRow = true;
        }
        currentCellX = firstCellOfPlane(0);
        currentCellY = firstCellOfPlane(1);
        currentCellZ = firstCellOfPlane(2);
        isFirstCellOfPlane = true;
    }

    if(currentCell != nullptr)
    {
        currentCell->nextCell = nullptr;
    }
    else
    {
        lastCell->nextCell = nullptr;
    }

    std::cout << "cubes : " << i << std::endl;

}


gridCell* VoxelGrid::getFirstCell()
{
    return this->firstCell;
}


std::string VoxelGrid::toString()
{
    int i=0;
    std::stringstream sstr;
    gridCell* temp = this->firstCell;
    while(temp != nullptr)
    {
        sstr << "Cube : " << std::endl;
        for(int i=0; i<8; i++)
        {
            sstr << "\t P" << i << " : (" << temp->points[i]->position(0) << ", " << temp->points[i]->position(1) << ", " << temp->points[i]->position(2) << ") - Val : " << temp->points[i]->value << std::endl;
        }
        sstr << std::endl;
        temp = temp->nextCell;
        i++;
    }

    std::cout << "cubes : " << i << std::endl;
    return sstr.str();
}


// Auxiliary methods


Plane* VoxelGrid::getnearestPlane(double x, double y, double z, Vertex* planeCenter, std::map<int, Plane*, classComp>& planes_map, kDTree& planesTree)
{
    std::vector<Vertex*> nearestPlaneVertex;
    std::map<int, Plane*, classComp>::iterator nearestPlane;
    // Find nearest plane from this point
    planeCenter->xyz(x, y, z);
    nearestPlaneVertex = planesTree.findKNN(planeCenter, 1);

    if((nearestPlane = planes_map.find(nearestPlaneVertex[0]->getId())) != planes_map.end())
    {
        return nearestPlane->second;
    }
    else
    {
        std::cerr << "[ERROR]: in VoxelGrid, plane center with center : ( " << x << ", " << y << ", " << z << ") is missing" << std::endl;
        exit(-1);
    }
}


double VoxelGrid::Hausdorff(Eigen::Vector3d p1, Eigen::Vector3d nearestPlaneCenter, Eigen::Vector3d planeNormal, kDTree& planesTree)
{
    Eigen::Vector3d z = nearestPlaneCenter - ((p1 - nearestPlaneCenter).dot(planeNormal))*planeNormal;
    Vertex temp(z(0), z(1), z(2));
    Vertex* nearestPoint = planesTree.findKNN(&temp, 1)[0];

    return std::sqrt( std::pow(z(0) - nearestPoint->x(), 2) + std::pow(z(1) - nearestPoint->y(), 2) + std::pow(z(2) - nearestPoint->z(), 2) );
}


bool VoxelGrid::computeCellPointValue(kDTree& planesTree, std::map<int, Plane*, classComp>& planes_map, Eigen::Vector3d point, double* val)
{
    Vertex temp;
    Plane* nearestPlane = getnearestPlane(point(0), point(1), point(2), &temp, planes_map, planesTree);
    Vertex* planeCenter = nearestPlane->center();
    Eigen::Vector3d pointProjectedOnPlane = point - Eigen::Vector3d(planeCenter->x(), planeCenter->y(), planeCenter->z());
    
    // Verify value's validity
    if(Hausdorff(point, Eigen::Vector3d(planeCenter->x(), planeCenter->y(), planeCenter->z()), nearestPlane->normal(), planesTree) < this->maxDistanceValue)
    {
        *val = pointProjectedOnPlane.dot(nearestPlane->normal());
        return true;
    }
    else
    {
        return false;
    }
}


gridCell* VoxelGrid::newCell(kDTree& planesTree, std::map<int, Plane*, classComp>& planes_map, double x0, double y0, double z0)
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
    if(!computeCellPointValue(planesTree, planes_map, PositionP0, &p0Value))
    {
        return nullptr;
    }
        // P1
    if(!computeCellPointValue(planesTree, planes_map, positionP1, &p1Value))
    {
        return nullptr;
    }
        // P2
    if(!computeCellPointValue(planesTree, planes_map, positionP2, &p2Value))
    {
        return nullptr;
    }
        // P3
    if(!computeCellPointValue(planesTree, planes_map, positionP3, &p3Value))
    {
        return nullptr;
    }
        // P4
    if(!computeCellPointValue(planesTree, planes_map, positionP4, &p4Value))
    {
        return nullptr;
    }
        // P5
    if(!computeCellPointValue(planesTree, planes_map, positionP5, &p5Value))
    {
        return nullptr;
    }
        // P6
    if(!computeCellPointValue(planesTree, planes_map, positionP6, &p6Value))
    {
        return nullptr;
    }
        // P7
    if(!computeCellPointValue(planesTree, planes_map, positionP7, &p7Value))
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
