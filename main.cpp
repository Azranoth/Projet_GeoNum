
#include "HalfEdge_structure/mesh.h"
#include "PlanesGraph_lib/PlanesGraph.h"

int main(int argc, char *argv[])
{
    //---- EX LEAST SQUARES WITH EIGEN
    MatrixXd A = MatrixXd::Random(3,2);
    std::cout << std::endl << A << std::endl;
    VectorXd b = VectorXd::Random(3);
    std::cout << std::endl << b << std::endl;
    std::cout << std::endl << A.jacobiSvd(ComputeThinU | ComputeThinV).solve(b) << std::endl;
    //--------------------------------

    return 0;
}

