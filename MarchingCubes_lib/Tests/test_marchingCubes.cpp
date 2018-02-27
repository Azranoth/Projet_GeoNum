#include "MarchingCubes.h"

int main(int argc, char* argv[]){

    double density = 0.3;
    double noise = 0.1;
    double epsilon = -0.1;

    double cubeSize = density + noise + epsilon;

    Vertex *v0 = new Vertex(5.5, -6, 5.5);
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

    VoxelGrid* vg_test = new VoxelGrid(planes, cubeSize, density, noise);

    MarchingCubes mCubes_test = MarchingCubes(vg_test);
    mCubes_test.exportToOFFFile("./testMarchingCubes1.off");
    mCubes_test.polygonization();
    mCubes_test.exportToOFFFile("./testMarchingCubes2.off");

    return 0;
}
