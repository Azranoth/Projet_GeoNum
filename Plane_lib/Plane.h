#ifndef __Plane_H
#define __Plane_H

#include <../Eigen/Eigen/Dense>
#include <../Eigen/Eigen/Eigenvalues>
#include <../Eigen/Eigen/SVD>

#include "mesh.h"

class Plane
{
// Attributes
private:
    Vertex* _center;
    Eigen::Vector3d _normal;
    bool _centerIsDefined;

// Constructors
public:

    Plane();


    Plane(Vertex* center, Eigen::Vector3d normal);


// Getters and setters
public:


    /**
     * @brief center return the center of the plane
     * @return
     */
    Vertex* center() const;


    /**
     * @brief center replace center with center0
     * @param center0
     */
    void center(Vertex* center0);


    /**
     * @brief normal return the normal of the plane
     * @return
     */
    Eigen::Vector3d normal() const;


    /**
     * @brief normal replace the normal with normal0
     * @param normal0
     */
    void normal(Eigen::Vector3d normal0);


// Methods
public:


    /**
     * @brief computeCentroid compute the center of the plane in 3D space with least square on the k nearest neighbors of the referent vertex with weight for each vertex
     * @param Vertices
     * @param weights
     */
    void computeCentroid(std::vector<Vertex*> vertices, Eigen::VectorXd weights);


    /**
     * @brief computeCentroid compute the center of the plane in 3D space with least square on the k nearest neighbors of the referent vertex
     * @param Vertices
     */
    void computeCentroid(std::vector<Vertex *> vertices);


    /**
     * @brief computeNormal compute the normal of the plane in 3D space based on the k nearest neighbors of the referent vertex with a covariance matrix
     * @param Vertices
     */
    void computeNormal(std::vector<Vertex *> vertices);
};


#endif
