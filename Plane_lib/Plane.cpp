#include "Plane.h"

// Constructor

Plane::Plane()
{
    this->_centerIsDefined = false;
    this->_center = nullptr;
    this->_normal = Eigen::Vector3d(3);
}


Plane::Plane(Vertex *center, Eigen::Vector3d normal)
{
    this->_center = center;
    this->_normal = normal;
    this->_centerIsDefined = true;
}


// Getters and setters


Vertex* Plane::center() const
{
    return this->_center;
}


void Plane::center(Vertex* center0)
{
    this->_center = center0;
    this->_centerIsDefined = true;
}


Eigen::Vector3d Plane::normal() const
{
    return this->_normal;
}


void Plane::normal(Eigen::Vector3d normal0)
{
    this->_normal = normal0;
}


// Methods


void Plane::computeCentroid(std::vector<Vertex *> vertices, Eigen::VectorXd weights)
{

    Eigen::VectorXd center0;

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

     center0 = verticesMatrix.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(weights);
     this->_center = new Vertex(center0(0), center0(1), center0(2));
     this->_centerIsDefined = true;
}


void Plane::computeCentroid(std::vector<Vertex *> vertices)
{
    Eigen::VectorXd center0;
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

    std::cout << "enculé" << std::endl;
    center0 = (verticesMatrix.transpose() * verticesMatrix).jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(verticesMatrix.transpose() * weights);
    std::cout << "enculé end" << std::endl;

    std::cout << "hey " << std::endl;
    this->_center = new Vertex(center0(0), center0(1), center0(2));
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
        x = vertices[i]->x() - this->_center->x();
        y = vertices[i]->y() - this->_center->y();
        z = vertices[i]->z() - this->_center->z();

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











