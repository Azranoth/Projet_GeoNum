#include <cassert>

#include "kDTree.h"
#include "mesh.h"

int main()
{
    std::string ctrl_string = "Root : (-5.200000, 2.000000, 14.300000), sep Axis : 0\n\tRoot : (-10.500000, 1.200000, 18.500000), sep Axis : 1\n\t\tRoot : (-25.200000, -2.000000, 17.800000), sep Axis : 2\n\t\t\tRoot : (-25.200000, -2.000000, 17.800000), sep Axis : 0\n\t\t\t\tLeaf : (-25.200000, -2.000000, 17.800000), sep Axis : 3\n\t\t\t\tLeaf : (-12.000000, 0.000000, 15.000000), sep Axis : 3\n\t\t\tLeaf : (-10.500000, 1.200000, 18.500000), sep Axis : 3\n\t\tLeaf : (-5.200000, 2.000000, 14.300000), sep Axis : 3\n\tRoot : (12.500000, 45.200000, -15.500000), sep Axis : 1\n\t\tRoot : (12.500000, 45.200000, -15.500000), sep Axis : 2\n\t\t\tLeaf : (12.500000, 45.200000, -15.500000), sep Axis : 3\n\t\t\tLeaf : (7.500000, 15.200000, 8.000000), sep Axis : 3\n\t\tLeaf : (15.000000, 25.500000, -12.000000), sep Axis : 3\n";

    // Create the tree object
    kDTree* tree = new kDTree();

    // Create the data set for test purpose
    std::map<int, Vertex*, classComp> vertices;
    Vertex* v1 = new Vertex(-12.0, 0.0, 15.0);
    Vertex* v2 = new Vertex(-10.5, 1.2, 18.5);
    Vertex* v3 = new Vertex(-5.2, 2.0, 14.3);
    Vertex* v4 = new Vertex(0.5, -12.0, -52.0);
    Vertex* v5 = new Vertex(15.0, 25.5, -12.0);
    Vertex* v6 = new Vertex(-25.2, -2.0, 17.8);
    Vertex* v7 = new Vertex(7.5, 15.2, 8.0);
    Vertex* v8 = new Vertex(12.5, 45.2, -15.5);

    vertices[v1->getId()] = v1;
    vertices[v2->getId()] = v2;
    vertices[v3->getId()] = v3;
    vertices[v4->getId()] = v4;
    vertices[v5->getId()] = v5;
    vertices[v6->getId()] = v6;
    vertices[v7->getId()] = v7;
    vertices[v8->getId()] = v8;

    // ------------
    // Test of init

    // Init the tree
    std::cout << "Begin test of tree initialization..." << std::endl;
    tree->init(vertices);
    std::string kDTree_str = tree->toString(0);
    assert(kDTree_str == ctrl_string);
    std::cout << "Test of tree initialization passed." << std::endl;

    // ---------------
    // Test of findKNN
    std::cout << "Begin test of tree findKNN method..." << std::endl;
    std::vector<Vertex*> vec_1NN;
    std::vector<Vertex*> vec_3NN;

    vec_1NN = tree->findKNN(v1, 1);
    vec_3NN = tree->findKNN(v1, 3);

    assert(vec_1NN[0] == v2);
    assert(vec_3NN[0] == v2);
    assert(vec_3NN[1] == v3);
    assert(vec_3NN[2] == v6);

    std::cout << "Test of tree findKNN method passed." << std::endl;

    return 0;
}
