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

void Vertex::xyz(double x0, double y0, double z0)
{
    this->_x = x0;
    this->_y = y0;
    this->_z = z0;
}

void Vertex::setChildEdge(HalfEdge* he){
    this->_childEdge = he;
}

void Vertex::display(){

    std::cout << "Vertex " << this->_id << " : Coordinates ( " << this->_x << " , " << this->_y << " , " << this->_z << " )" << std::endl;
}

double Vertex::barycentricArea(){
    // Process barycenter of every triangle having this point as a vertex
    std::vector<Vertex> listOfBarycentres;
    // Keeping first neighbour vertex in memory
    Vertex* firstNBVertex = this->_childEdge->getTeteBeche()->getSourceVertex();
    HalfEdge* teteBeche = this->_childEdge->getTeteBeche();
    Vertex* nextNBVertex = teteBeche->getNextHalfEdge()->getTeteBeche()->getSourceVertex();
    teteBeche = teteBeche->getNextHalfEdge()->getTeteBeche();

    Vertex bary, halfEdgeMiddle;
    double baryX, baryY, baryZ, middleX, middleY, middleZ;
    // Get first face barycentric coordinates (i.e the first face with firstNBVertex as a vertex)
    baryX = (this->_x + firstNBVertex->x() + nextNBVertex->x())/3;
    baryY = (this->_y + firstNBVertex->y() + nextNBVertex->y())/3;
    baryZ = (this->_z + firstNBVertex->z() + nextNBVertex->z())/3;
    bary = Vertex(baryX, baryY, baryZ);

    middleX = (this->_x + firstNBVertex->x())/2;
    middleY = (this->_y + firstNBVertex->y())/2;
    middleZ = (this->_z + firstNBVertex->z())/2;
    halfEdgeMiddle = Vertex(middleX, middleY, middleZ);

    listOfBarycentres.push_back(halfEdgeMiddle);
    listOfBarycentres.push_back(bary);

    nextNBVertex = nextNBVertex->getChildEdge()->getTeteBeche()->getSourceVertex();
    Vertex* followingNextNB = teteBeche->getNextHalfEdge()->getTeteBeche()->getSourceVertex();
    teteBeche = teteBeche->getNextHalfEdge()->getTeteBeche();
    // Until we have processed every neighbour vertices around the main vertex
    while(nextNBVertex != firstNBVertex){

        // Calculate barycentric coordinates of the current face with the current nextNBVertex && middle of the segment between this vertex & the current one
        baryX = (this->_x + nextNBVertex->x() + followingNextNB->x())/3;
        baryY = (this->_y + nextNBVertex->y() + followingNextNB->y())/3;
        baryZ = (this->_z + nextNBVertex->z() + followingNextNB->z())/3;
        bary = Vertex(baryX, baryY, baryZ);

        middleX = (this->_x + nextNBVertex->x())/2;
        middleY = (this->_y + nextNBVertex->y())/2;
        middleZ = (this->_z + nextNBVertex->z())/2;
        halfEdgeMiddle = Vertex(middleX, middleY, middleZ);

        listOfBarycentres.push_back(halfEdgeMiddle);
        listOfBarycentres.push_back(bary);

        nextNBVertex = followingNextNB;
        followingNextNB = teteBeche->getNextHalfEdge()->getTeteBeche()->getSourceVertex();
        teteBeche = teteBeche->getNextHalfEdge()->getTeteBeche();
    }

    // Calculate the barycentric area
    double area = 0;
    unsigned int j = listOfBarycentres.size()-1;
    for(unsigned int i = 0; i < listOfBarycentres.size(); i++){
        area += (listOfBarycentres.data()[j].x() + listOfBarycentres.data()[i].x())
                * (listOfBarycentres.data()[j].y() - listOfBarycentres.data()[i].y())
                * (listOfBarycentres.data()[j].z() + listOfBarycentres.data()[i].z());
        j = i;
    }

    return area;
}

double Vertex::voronoiArea(){
    // Starting from the 2nd neighboor vertex
    HalfEdge* currentNBTeteBeche = this->getChildEdge()->getTeteBeche()->getNextHalfEdge()->getTeteBeche();
    Vertex* firstNBVertex = currentNBTeteBeche->getSourceVertex();
    Vertex* currentNBVertex = firstNBVertex;
    // Previous one is then the first vertex
    HalfEdge* prevNBTeteBeche = this->getChildEdge()->getTeteBeche();
    Vertex* prevNBVertex = prevNBTeteBeche->getSourceVertex();
    // Next neighboor vertex, initialy the 3rd one
    HalfEdge* nextNBTeteBeche = currentNBTeteBeche->getNextHalfEdge()->getTeteBeche();
    Vertex* nextNBVertex = nextNBTeteBeche->getSourceVertex();

    double voronoiAreaSum = 0.0;

    do{
        // Angle = arccos( (vec1.vec2) / (|vec1|*|vec2|) )
        // Note : here the Vertex class is used as a vector class, just to store coordinates, providing a fast access to them.

        //-------Next Vertex angle
        Vertex* vec1 = new Vertex(this->x() - nextNBVertex->x(),
                                  this->y() - nextNBVertex->y(),
                                  this->z() - nextNBVertex->z());

        Vertex* vec2 = new Vertex(currentNBVertex->x() - nextNBVertex->x(),
                                  currentNBVertex->y() - nextNBVertex->y(),
                                  currentNBVertex->z() - nextNBVertex->z());

        double dot = vec1->x()*vec2->x() + vec1->y()*vec2->y() + vec1->z()*vec2->z();
        double vec1Lenght = std::sqrt(vec1->x()*vec1->x() + vec1->y()*vec1->y() + vec1->z()*vec1->z());
        double vec2Lenght = std::sqrt(vec2->x()*vec2->x() + vec2->y()*vec2->y() + vec2->z()*vec2->z());

        double angleNextVertex = std::acos(dot/(vec1Lenght*vec2Lenght));


        //-------Prev Vertex angle
        vec1 = new Vertex(  this->x() - prevNBVertex->x(),
                            this->y() - prevNBVertex->y(),
                            this->z() - prevNBVertex->z());

        vec2 = new Vertex(  currentNBVertex->x()-prevNBVertex->x(),
                            currentNBVertex->y()-prevNBVertex->y(),
                            currentNBVertex->z()-prevNBVertex->z());

        dot = vec1->x()*vec2->x() + vec1->y()*vec2->y() + vec1->z()*vec2->z();
        vec1Lenght = std::sqrt(vec1->x()*vec1->x() + vec1->y()*vec1->y() + vec1->z()*vec1->z());
        vec2Lenght = std::sqrt(vec2->x()*vec2->x() + vec2->y()*vec2->y() + vec2->z()*vec2->z());

        double anglePrevVertex = std::acos(dot/(vec1Lenght*vec2Lenght));
        //-------

        // Add current point's voronoi area value to the sum
        double distBetweenThisAndCurrent = std::sqrt(   (currentNBVertex->x() - this->x())*(currentNBVertex->x() - this->x())
                                                      + (currentNBVertex->y() - this->y())*(currentNBVertex->y() - this->y())
                                                      + (currentNBVertex->z() - this->z())*(currentNBVertex->z() - this->z()));
        voronoiAreaSum = voronoiAreaSum + ( 1/tan(angleNextVertex) + 1/tan(anglePrevVertex)) * std::abs(distBetweenThisAndCurrent)*std::abs(distBetweenThisAndCurrent);

        // Set pointers to next vertices
        prevNBVertex = currentNBVertex;
        prevNBTeteBeche = currentNBTeteBeche;

        currentNBVertex = nextNBVertex;
        currentNBTeteBeche = nextNBTeteBeche;

        nextNBTeteBeche = nextNBTeteBeche->getNextHalfEdge()->getTeteBeche();
        nextNBVertex = nextNBTeteBeche->getSourceVertex();


    } while(currentNBVertex != firstNBVertex); // Continue until every neighboor vertex as been processed

    std::cout << voronoiAreaSum << std::endl;
    return (1./8.)*voronoiAreaSum;
}

// Operators overload

bool Vertex::operator==(Vertex& other)
{
    return (this->x() == other.x()) && (this->y() == other.y()) && (this->z() == other.z());
}
