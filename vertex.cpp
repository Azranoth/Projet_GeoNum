#include "vertex.h"

int Vertex::NB_VERTICES = 0;

Vertex::Vertex(){

    this->_id = Vertex::NB_VERTICES++;
    this->_x = 0.0;
    this->_y = 0.0;
    this->_z = 0.0;
    this->_childEdge = NULL;
}

Vertex::Vertex(double x, double y, double z){

    this->_id = Vertex::NB_VERTICES++;
    this->_x = x;
    this->_y = y;
    this->_z = z;
    this->_childEdge = NULL;
}

Vertex::Vertex(double x, double y, double z, HalfEdge* childEdge){

    this->_id = Vertex::NB_VERTICES++;
    this->_x = x;
    this->_y = y;
    this->_z = z;
    this->_childEdge = childEdge;
}

void Vertex::setChildEdge(HalfEdge* he){
    this->_childEdge = he;
}

void Vertex::display(){

    std::cout << "Vertex " << this->_id << " : Coordinates ( " << this->_x << " , " << this->_y << " , " << this->_z << " )" << std::endl;
}

double Vertex::barycentricArea(){
    // Calcul de tous les barycentres des triangles ayant v pour sommet
    std::vector<Vertex> listOfBarycentres;
    // Keeping first neighbour vertex in memory
    Vertex* firstNBVertex = this->_childEdge->getTeteBeche()->getSourceVertex();
    Vertex bary;
    double baryX, baryY, baryZ;
    // Get first face barycentric coordinates (i.e the first face with firstNBVertex as a vertex
    baryX = (this->_x + firstNBVertex->x() + firstNBVertex->getChildEdge()->getTeteBeche()->getSourceVertex()->x())/3;
    baryY = (this->_y + firstNBVertex->y() + firstNBVertex->getChildEdge()->getTeteBeche()->getSourceVertex()->y())/3;
    baryX = (this->_z + firstNBVertex->z() + firstNBVertex->getChildEdge()->getTeteBeche()->getSourceVertex()->z())/3;
    bary = Vertex(baryX, baryY, baryZ);
    listOfBarycentres.push_back(bary);

    Vertex* nextNBVertex = firstNBVertex->getChildEdge()->getTeteBeche()->getSourceVertex();
    // Until we have processed every neighbour vertices around the main vertex
    while(nextNBVertex != firstNBVertex){
        // Calculate barycentric coordinates of the current face with the current nextNBVertex
        baryX = (this->_x + nextNBVertex->x() + nextNBVertex->getChildEdge()->getTeteBeche()->getSourceVertex()->x())/3;
        baryY = (this->_y + nextNBVertex->y() + nextNBVertex->getChildEdge()->getTeteBeche()->getSourceVertex()->y())/3;
        baryX = (this->_z + nextNBVertex->z() + nextNBVertex->getChildEdge()->getTeteBeche()->getSourceVertex()->z())/3;
        bary = Vertex(baryX, baryY, baryZ);
        listOfBarycentres.push_back(bary);

        nextNBVertex = nextNBVertex->getChildEdge()->getTeteBeche()->getSourceVertex();
    }

    // Calculate the barycentric area
    double sum = 0;



}
