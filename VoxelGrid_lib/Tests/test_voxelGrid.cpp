#include "VoxelGrid.h"


int main()
{
    // Init planes of a cube (0, 1, 0), (1, -1, 1)

    double density = 0.3;
    double noise = 0.1;
    double epsilon = -0.1;

    double cubeSize = density + noise + epsilon;

//    Vertex *cv0 = new Vertex(0, 1, 0);
//    Vertex *cv1 = new Vertex(1, 1, 0);
//    Vertex *cv2 = new Vertex(1, 1, 1);
//    Vertex *cv3 = new Vertex(0, 1, 1);
//    Vertex *cv4 = new Vertex(0, -1, 0);
//    Vertex *cv5 = new Vertex(1, -1, 0);
//    Vertex *cv6 = new Vertex(1, -1, 1);
//    Vertex *cv7 = new Vertex(0, -1, 1);

//    std::vector<Vertex*> vertices;
//    vertices.push_back(cv0);
//    vertices.push_back(cv1);
//    vertices.push_back(cv2);
//    vertices.push_back(cv3);
//    vertices.push_back(cv4);
//    vertices.push_back(cv5);
//    vertices.push_back(cv6);
//    vertices.push_back(cv7);

    Vertex *v0 = new Vertex(0.5, -1, 0.5);
    Vertex *v1 = new Vertex(0.5, 0, 0.5);
    Vertex *v2 = new Vertex(1, 0, 0.5);
    Vertex *v3 = new Vertex(0.5, 0, 1);
    Vertex *v4 = new Vertex(0, 0, 0.5);
    Vertex* v5 = new Vertex(0.5, 1, 0.5);

    Plane* p0 = new Plane(v0, Vector3d(0.0, -1.0, 0.0));
    Plane* p1 = new Plane(v1, Vector3d(-1.0, 0.0, 0.0));
    Plane* p2 = new Plane(v2, Vector3d(0.0, 0.0, -1));
    Plane* p3 = new Plane(v3, Vector3d(1.0, 0.0, 0.0));
    Plane* p4 = new Plane(v4, Vector3d(0.0, 0.0, 1.0));
    Plane* p5 = new Plane(v5, Vector3d(0.0, 1.0, 0.0));

    std::vector<Plane*> planes;
    planes.push_back(p0);
    planes.push_back(p1);
    planes.push_back(p2);
    planes.push_back(p3);
    planes.push_back(p4);
    planes.push_back(p5);

    // Test of grid construction
    std::cout << "Begin test of grid construction..." << std::endl;
    VoxelGrid vg_test = VoxelGrid(planes, cubeSize, density, noise);
    std::cout << vg_test.toString() << std::endl;
    std::cout << "Test of grid construction passed." << std::endl;

    return 0;
}
