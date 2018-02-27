
#include "mesh.h"
#include "kDTree.h"
#include "Plane.h"
#include "PlanesGraph.h"
#include "VoxelGrid.h"
#include "MarchingCubes.h"



int main(int argc, char *argv[])
{
    std::string fileRepository = "OFF/";
    std::string fileName = "almost_torus.off";

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
    double density = 0.3;
    double noise = 0.1;
    double epsilon = -0.1;
    double cubeSize = density + noise + epsilon;

    Mesh* msh = new Mesh();

    msh->importOFF(fileRepository + fileName);

    kd_tree->init(msh->getVertices());

    int i=-1;
    for(it = msh->getVertices().begin(); it != msh->getVertices().end(); ++it)
    {

        i++;
        std::cout << " i : " << i << "/" << msh->getVertices().size() << std::endl;
        bool b = it == msh->getVertices().end();
        std::cout << "it == end ? : " << b << std::endl;
        std::cout << "hey " << it->first << std::endl;
        std::cout << "(" <<  it->second->x() << ", " << it->second->y() << ", " << it->second->z() << ")" << std::endl;
        std::cout << "HEY findKNN ! " << std::endl;
        vertices = kd_tree->findKNN((*it).second, 8);
        std::cout << "HEY findKNN end ! " << std::endl;
        std::cout << "HEY insert ! " << std::endl;
        vertices.insert(vertices.begin(), (*it).second );
        std::cout << "HEY insert end ! " << std::endl;

        std::cout << "HEY for ! " << std::endl;
        Eigen::VectorXd weights(vertices.size());
        int i = 0;
        for(itV = vertices.begin(); itV != vertices.end(); ++itV){

            if(i == 0)
                weights(0) = 0.0;
            else
                weights(i) = kd_tree->euclideanDistance((*it).second, (*itV));
            i++;
        }
        std::cout << "HEY for end ! " << std::endl;

        newPlane = new Plane();
        std::cout << "HEY center ! " << std::endl;
        newPlane->computeCentroid(vertices, weights);
        std::cout << "HEY center end! " << std::endl;
        std::cout << "HEY normal ! " << std::endl;
        newPlane->computeNormal(vertices);
        std::cout << "HEY normal end ! " << std::endl;
        std::cout << "HEY push_back ! " << std::endl;
        planes.push_back(newPlane);
        std::cout << "HEY push_back end ! " << std::endl;
    }

    std::cout << "HEY ! " << std::endl;

    graph = new PlanesGraph(planes);
    MST = graph->kruskal();

    grid = new VoxelGrid(planes, cubeSize, density, noise);

    MarchingCubes* MCubes = new MarchingCubes(grid);
    MCubes->polygonization();
    MCubes->exportToOFFFile("./resultHoppe.off");

    return 0;
}

