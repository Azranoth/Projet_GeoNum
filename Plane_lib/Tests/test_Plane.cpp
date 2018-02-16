#include "Plane.h"


int main()
{
    // Set up the test environment
    Plane test_plane;

    // Ref point
    Vertex* v1 = new Vertex(0.0, 0.0, 0.0);
    // K nearest neighbors
    Vertex* v2 = new Vertex(1.0, 0.0, 0.0);
    Vertex* v3 = new Vertex(0.0, 1.0, 0.0);
    Vertex* v4 = new Vertex(1.0, 1.0, 0.0);
    Vertex* v5 = new Vertex(1.0, 0.0, 1.0);

    std::vector<Vertex*> vertices_vector;
    Eigen::VectorXd weights(5);

    vertices_vector.push_back(v1);
    vertices_vector.push_back(v2);
    vertices_vector.push_back(v3);
    vertices_vector.push_back(v4);
    vertices_vector.push_back(v5);

    weights(0) = 0.0;
    weights(1) = 1.0;
    weights(2) = 1.0;
    weights(3) = 1.0/2.0;
    weights(4) = 1.0/2.0;


    // Test of computeCentroid with same weight for each vertex
    std::cout << "Begin test of computeCentroid with same weight for each vertex..." << std::endl;
    test_plane.computeCentroid(vertices_vector);
    assert((test_plane.center()(0) >= 0.65) && (test_plane.center()(0) <= 0.67));
    assert((test_plane.center()(1) >= 0.65) && (test_plane.center()(1) <= 0.67));
    assert((test_plane.center()(2) >= 0.33) && (test_plane.center()(2) <= 0.34));
    std::cout << "Test of computeCentroid with same weight passed." << std::endl;

    // Test of computeCentroid with weight based on euclidiean distance
    std::cout << "Begin test of computeCentroid with wieght based on euclidean distance..." << std::endl;
    test_plane.computeCentroid(vertices_vector, weights);
    assert((test_plane.center()(0) >= 0.49) && (test_plane.center()(0) <= 0.51));
    assert((test_plane.center()(1) >= 0.49) && (test_plane.center()(1) <= 0.51));
    assert((test_plane.center()(2) >= 0.0) && (test_plane.center()(2) <= 0.01));
    std::cout << "Test of computeCentroid with weights based on eucliden distance passed." << std::endl;

    // Test of computeNormal
    std::cout << "Begin test of computeNormal..." << std::endl;
    test_plane.computeNormal(vertices_vector);
    assert((test_plane.normal()(0) >= 0.1) && (test_plane.normal()(0) <= 0.11));
    assert((test_plane.normal()(1) >= -0.547) && (test_plane.normal()(1) <= -0.546));
    assert((test_plane.normal()(2) >= -0.347) && (test_plane.normal()(2) <= -0.346));
    std::cout << "Test of computeNormal passed." << std::endl;

    return 0;
}
