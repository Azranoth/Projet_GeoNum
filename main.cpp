
#include "HalfEdge_structure/mesh.h"

int main(int argc, char *argv[])
{

    std::string filename = "../OFF/block.off";
    Mesh mesh = Mesh();
    mesh.importOFF(filename.c_str());
    mesh.exportOFF("../OFF/export_test.off");
    //mesh.display();

    return 0;
}

