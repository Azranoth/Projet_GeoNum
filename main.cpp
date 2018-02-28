
#include "mesh.h"
#include "kDTree.h"
#include "Plane.h"
#include "PlanesGraph.h"
#include "VoxelGrid.h"
#include "MarchingCubes.h"



int main(int argc, char *argv[])
{
    int k = 15;
    std::string fileRepository = "OFF/";
    std::string fileName = "block.off";

    // Containers
    std::vector<Vertex*> vertices;
    std::vector<Plane*> planes;
    kDTree* kd_tree = new kDTree();

    // Iterators
    std::vector<Vertex*>::iterator itV;
    std::map<int, Vertex*>::iterator it;

    // Variables
    Plane* newPlane;
    PlanesGraph* graph;
    std::vector<Plane*> MST;
    VoxelGrid* grid;

    // Used for voxelgrid creation
    double density = 0.5;
    double noise = 0.1;
    double cubeSize = 0.58;

    Mesh* msh = new Mesh();

    msh->importOFF(fileRepository + fileName);

    kd_tree->init(msh->getVertices());


    for(unsigned int x=0; x<msh->getVertices().size(); x++)
    {
        auto it = msh->getVertices().find(x);

        vertices = kd_tree->findKNN((*it).second, k);
        vertices.insert(vertices.begin(), (*it).second );

        newPlane = new Plane();
        newPlane->computeCentroid(vertices);
//        if(newPlane->center()->x()>25 || newPlane->center()->x()<-25 || newPlane->center()->y()>25 || newPlane->center()->y()<-25 || newPlane->center()->z()>25 || newPlane->center()->z()<-25)
//        {
//            std::cout << "mauvais : " << std::endl;
//            std::cout << "(" << newPlane->center()->x() << ", " << newPlane->center()->y() << ", " << newPlane->center()->z() << ")" << std::endl;
//            std::cout << weights << std::endl;
//        }

        newPlane->computeNormal(vertices);
        planes.push_back(newPlane);
    }


    graph = new PlanesGraph(planes, k);
    graph->kruskal();

    grid = new VoxelGrid(planes, cubeSize, density, noise);

    MarchingCubes* MCubes = new MarchingCubes(grid);
    MCubes->polygonization();
    MCubes->exportToOFFFile("./resultHoppe.off");

    return 0;
}

