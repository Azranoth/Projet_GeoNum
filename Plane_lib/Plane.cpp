#include "Plane.h"

// Constructor

Plane::Plane()
{
    this->_centerIsDefined = false;
    this->_center = Eigen::VectorXd(3);
    this->_normal = Eigen::VectorXd(3);
}


Plane::Plane(Eigen::VectorXd center, Eigen::VectorXd normal)
{
    this->_center = center;
    this->_normal = normal;
    this->_centerIsDefined = true;
}


// Getters and setters

Eigen::VectorXd Plane::center() const
{
    return this->_center;
}


void Plane::center(Eigen::VectorXd center0)
{
    this->_center = center0;
    this->_centerIsDefined = true;
}


Eigen::VectorXd Plane::normal() const
{
    return this->_normal;
}


void Plane::normal(Eigen::VectorXd normal0)
{
    this->_normal = normal0;
}


// Methods


void Plane::computeCentroid(std::vector<Vertex *> vertices, Eigen::VectorXd weights)
{

    if(weights.size() != static_cast<unsigned int>(vertices.size()))
    {
        std::cerr << "[WARNING]: in Plane, vertices matrix and weights vector have different size" << std::endl;
    }

     Eigen::MatrixXd verticesMatrix(vertices.size(), 3);

     // Create matrix
     for(unsigned int i=0; i<vertices.size(); i++)
     {
         verticesMatrix(i, 0) = vertices[i]->x();
         verticesMatrix(i, 1) = vertices[i]->y();
         verticesMatrix(i, 2) = vertices[i]->z();
     }

     this->_center = verticesMatrix.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(weights);
     this->_centerIsDefined = true;
}


void Plane::computeCentroid(std::vector<Vertex *> vertices)
{
    Eigen::MatrixXd verticesMatrix(vertices.size(), 3);
    Eigen::VectorXd weights(vertices.size());


    // Create matrix
    for(unsigned int i=0; i<vertices.size(); i++)
    {
        weights(i) = 1.0;

        verticesMatrix(i, 0) = vertices[i]->x();
        verticesMatrix(i, 1) = vertices[i]->y();
        verticesMatrix(i, 2) = vertices[i]->z();
    }

    //this->_center = verticesMatrix.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(weights);
    this->_center = (verticesMatrix.transpose() * verticesMatrix).jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(verticesMatrix.transpose() * weights);
    this->_centerIsDefined = true;
}


void Plane::computeNormal(std::vector<Vertex *> vertices)
{
    if(!this->_centerIsDefined)
    {
        std::cerr << "[WARNING]: in Plane, center was not defined before normal computation" << std::endl;
    }

    Eigen::MatrixXd covariance(3,3);
    covariance(0,0) = 1.0;
    covariance(1,1) = 1.0;
    covariance(2,2) = 1.0;
    Eigen::MatrixXd temp(3,3);
    Eigen::VectorXcd maxEigenValue;
    Eigen::VectorXcd eigenValues;
    Eigen::MatrixXd eigenVectors;
    Eigen::EigenSolver<Eigen::MatrixXd> covariance_es;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    // Covariance matrix initialization
    for(unsigned int i = 0; i<vertices.size(); i++)
    {
        x = vertices[i]->x() - this->_center(0);
        y = vertices[i]->y() - this->_center(1);
        z = vertices[i]->z() - this->_center(2);

        temp(0,0) = x*x;
        temp(1,1) = y*y;
        temp(2,2) = z*z;

        covariance += temp;
    }


    covariance_es.compute(covariance, true);
    eigenValues = covariance_es.eigenvalues();
    eigenVectors = covariance_es.eigenvectors().real();

    // Find the maximum eigen value in the given eigen values
    // Each eigen values are stored in a different row
    // Each eigen vectors are stored in a different column

    maxEigenValue = eigenValues.row(0);
    this->_normal = eigenVectors.col(0);

    if(eigenValues.row(0).isMuchSmallerThan(eigenValues.row(1)))
    {
        maxEigenValue = eigenValues.row(1);
        this->_normal = eigenVectors.col(1);
    }
    if(maxEigenValue.isMuchSmallerThan(eigenValues.row(2)))
    {
        this->_normal = eigenVectors.col(2);
    }

}











