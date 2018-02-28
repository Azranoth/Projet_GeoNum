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

    Eigen::Vector3d temp;
    Eigen::Vector3d center0;

    if(weights.size() != static_cast<unsigned int>(vertices.size()))
    {
        std::cerr << "[WARNING]: in Plane, vertices matrix and weights vector have different size" << std::endl;
    }

     // Create matrix
     for(unsigned int i=0; i<vertices.size(); i++)
     {
         temp(0) = vertices[i]->x();
         temp(1) = vertices[i]->y();
         temp(2) = vertices[i]->z();

         center0 = center0 + (temp * weights(i));
     }

     this->_center = new Vertex(center0(0)/vertices.size(), center0(1)/vertices.size(), center0(2)/vertices.size());
     this->_centerIsDefined = true;
}


void Plane::computeCentroid(std::vector<Vertex *> vertices)
{
    Eigen::Vector3d temp = Eigen::Vector3d::Zero();
    Eigen::Vector3d center0 = Eigen::Vector3d::Zero();

    std::cout << "HEY !" << std::endl;
     // Create matrix
     for(unsigned int i=0; i<vertices.size(); i++)
     {
         temp(0) = vertices[i]->x();
         temp(1) = vertices[i]->y();
         temp(2) = vertices[i]->z();

         center0 = center0 + temp;
     }
     std::cout << "HEY ! end" << std::endl;

     std::cout << "HEY 2 ! " << std::endl;
     this->_center = new Vertex(center0(0)/vertices.size(), center0(1)/vertices.size(), center0(2)/vertices.size());
     std::cout << "HEY 2 ! end" << std::endl;
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











