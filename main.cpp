
#include "HalfEdge_structure/mesh.h"
#include <Eigen/Eigen/Dense>

using namespace Eigen;
int main(int argc, char *argv[])
{

    std::string filename = "../OFF/block.off";
    Mesh mesh = Mesh();
   // mesh.importOFF(filename.c_str());
   // mesh.exportOFF("../OFF/export_test.off");
   // mesh.display();

    //------ VORONOI AREA TEST
    Vertex *v0 = new Vertex(4, 3, 1);
    Vertex *v1 = new Vertex(6, 5, 2);
    Vertex *v2 = new Vertex(6, 2, 3);
    Vertex *v3 = new Vertex(4, 0, 1);
    Vertex *v4 = new Vertex(1, 1, 0);
    Vertex *v5 = new Vertex(3, 5, 1);


    HalfEdge* HEv1 = new HalfEdge(v0);
    HalfEdge* HEv2 = new HalfEdge(v0);
    HalfEdge* HEv3 = new HalfEdge(v0);
    HalfEdge* HEv4 = new HalfEdge(v0);
    HalfEdge* HEv5 = new HalfEdge(v0);

    HalfEdge* TBv1 = new HalfEdge(v1);
    HalfEdge* TBv2 = new HalfEdge(v2);
    HalfEdge* TBv3 = new HalfEdge(v3);
    HalfEdge* TBv4 = new HalfEdge(v4);
    HalfEdge* TBv5 = new HalfEdge(v5);

    HEv1->setTeteBeche(TBv1);
    HEv2->setTeteBeche(TBv2);
    HEv3->setTeteBeche(TBv3);
    HEv4->setTeteBeche(TBv4);
    HEv5->setTeteBeche(TBv5);

    TBv1->setTeteBeche(HEv1);
    TBv2->setTeteBeche(HEv2);
    TBv3->setTeteBeche(HEv3);
    TBv4->setTeteBeche(HEv4);
    TBv5->setTeteBeche(HEv5);

    HEv1->getTeteBeche()->setNextHalfEdge(HEv2);
    HEv2->getTeteBeche()->setNextHalfEdge(HEv3);
    HEv3->getTeteBeche()->setNextHalfEdge(HEv4);
    HEv4->getTeteBeche()->setNextHalfEdge(HEv5);
    HEv5->getTeteBeche()->setNextHalfEdge(HEv1);

    v0->setChildEdge(HEv1);
    v1->setChildEdge(TBv1);
    v2->setChildEdge(TBv2);
    v3->setChildEdge(TBv3);
    v4->setChildEdge(TBv4);
    v5->setChildEdge(TBv5);

    std::cout << v0->voronoiArea() << std::endl;
    //----------------------------------------

    //---- EX LEAST SQUARES WITH EIGEN
    MatrixXd A = MatrixXd::Random(3,2);
    std::cout << std::endl << A << std::endl;
    VectorXd b = VectorXd::Random(3);
    std::cout << std::endl << b << std::endl;
    std::cout << std::endl << A.jacobiSvd(ComputeThinU | ComputeThinV).solve(b) << std::endl;
    //--------------------------------

    return 0;
}

