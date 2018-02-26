#include "kDTree.h"


// Constructors and destructor

kDTree::kDTree()
{
    this->father = nullptr;
    this->firstChild = nullptr;
    this->secondCHild = nullptr;
    this->isLeaf = false;
    this->separationAxis = none;
    this->point = nullptr;
}

kDTree::kDTree(kDTree *father, Vertex *pt)
{
    this->father = father;
    this->firstChild = nullptr;
    this->secondCHild = nullptr;
    this->isLeaf = true;
    this->separationAxis = none;
    this->point = pt;
}


kDTree::kDTree(kDTree* father, kDTree* firstChild, kDTree* secondCHild, Vertex* pt, enum enum_separationAxis sepAxis)
{
    this->father = father;
    this->firstChild = firstChild;
    this->secondCHild = secondCHild;
    this->isLeaf = false;
    this->point = pt;
    this->separationAxis = sepAxis;
}


kDTree::~kDTree()
{
    if(!this->isLeaf)
    {
        if(this->firstChild != nullptr)
        {
            delete this->firstChild;
        }
        if(this->secondCHild != nullptr)
        {
            delete this->secondCHild;
        }
    }
}


// Getters and setters

kDTree* kDTree::getFather()
{
    return this->father;
}

void kDTree::setFather(kDTree *newFather)
{
    this->father = newFather;
}

kDTree* kDTree::getFirstChild()
{
    return this->firstChild;
}

void kDTree::setFirstChild(kDTree *newNode)
{
    this->firstChild = newNode;
}

kDTree* kDTree::getSecondChild()
{
    return this->secondCHild;
}

void kDTree::setSecondChild(kDTree* newNode)
{
    this->secondCHild = newNode;
}

bool kDTree::isLeafNode() const
{
    return this->isLeaf;
}

void kDTree::isLeafNode(bool newValue)
{
    this->isLeaf = newValue;
}

Vertex* kDTree::getPoint()
{
    return this->point;
}

void kDTree::setPoint(Vertex *point)
{
    this->point = point;
}

enum enum_separationAxis kDTree::getSeparationAxis()
{
    return this->separationAxis;
}


// Auxiliary methods

Vertex* kDTree::bissectricePoint(Vertex* v1, Vertex *v2)
{
    double x = (v2->x() + v1->x())/2;
    double y = (v2->y() + v1->y())/2;
    double z = (v2->z() + v1->z())/2;

    return new Vertex(x, y, z);
}

kDTree* kDTree::recursiveInitialization(std::vector<Vertex *> pointsList, enum enum_separationAxis divisionAxis)
{
    // lists of points on each side of the bissectrice
    std::vector<Vertex*>firstPart;
    std::vector<Vertex*>secondPart;
    kDTree* fstChild;
    kDTree* scdChild;
    kDTree* answ;
    Vertex* bissectricePoint;

    // End of the recursion
    if(pointsList.size() == 1)
    {
        answ = new kDTree(nullptr, *pointsList.begin());
        return answ;
    }

    switch(divisionAxis)
    {
        // X separation
        case separationIsOnX :
            // Sort the points on x coordinates
            std::sort(pointsList.begin(), pointsList.end(), classCompOnY());
            break;
        // Y separation
        case separationIsOnY :
            // Sort the points on y coordinates
            std::sort(pointsList.begin(), pointsList.end(), classCompOnX());
            break;
        // Z separation
        case separationIsOnZ :
            // Sort the points on z coordinates
            std::sort(pointsList.begin(), pointsList.end(), classCompOnZ());
            break;
        default :
            std::cerr << "[WARNING]: in kDTree::recursiveInitialization - invalid axis enum" << std::endl;
            exit(1);
    }

    // Separate the vector in twice to get sets of points on each side of the bissectrice
    if(pointsList.size() != 2)
    {
        firstPart = std::vector<Vertex*>(pointsList.begin(), pointsList.begin() + (pointsList.size()/2)+1);
        secondPart = std::vector<Vertex*>((pointsList.begin() + (pointsList.size()/2))+1, pointsList.end());
    }
    else
    {
        firstPart.push_back(pointsList.front());
        secondPart.push_back(pointsList.back());
    }


    // Get bissectrice point
    //bissectricePoint = this->bissectricePoint(firstPart.back(), *secondPart.begin());
    bissectricePoint = firstPart.back();

    switch(divisionAxis)
    {
        case separationIsOnX :
            fstChild = this->recursiveInitialization(firstPart, separationIsOnY);
            scdChild = this->recursiveInitialization(secondPart, separationIsOnY);
            break;
        case separationIsOnY :
            fstChild = this->recursiveInitialization(firstPart, separationIsOnZ);
            scdChild = this->recursiveInitialization(secondPart, separationIsOnZ);
            break;
        case separationIsOnZ :
            fstChild = this->recursiveInitialization(firstPart, separationIsOnX);
            scdChild = this->recursiveInitialization(secondPart, separationIsOnX);
            break;
        default :
            std::cerr << "[WARNING]: in kDTree::recursiveInitialization - invalid axis enum" << std::endl;
            exit(1);
    }

    answ = new kDTree(nullptr, fstChild, scdChild, bissectricePoint, divisionAxis);
    fstChild->setFather(answ);
    scdChild->setFather(answ);

    return answ;
}


float kDTree::euclideanDistance(const Vertex *v1, const Vertex *v2) const
{
    return std::sqrt( std::pow(v2->x() - v1->x(), 2) + std::pow(v2->y() - v1->y(), 2) + std::pow(v2->z() - v1->z(), 2));
}


void kDTree::recursiveSearch_kNearestNeighbors(const Vertex *refPoint, kDTree *node, const unsigned int neighborsNumbers)
{
    bool firstSubTreeBefore = true;
    float distance = 0.0f;
    Point currentPoint;

    if(node->point == refPoint)
    {
        return;
    }

    distance = this->euclideanDistance(refPoint, node->point);

    if(node->isLeafNode())
    {
        currentPoint.pt =  node->point;
        currentPoint.distanceFromRefPoint = distance;

        if(this->vectorKNN.size() == neighborsNumbers)
        {
            if(distance < this->vectorKNN.back().distanceFromRefPoint)
            {
                this->vectorKNN.back() = currentPoint;
                std::sort(this->vectorKNN.begin(), this->vectorKNN.end(), pointComparisonClass());
            }
        }
        else
        {
            this->vectorKNN.push_back(currentPoint);
            std::sort(this->vectorKNN.begin(), this->vectorKNN.end(), pointComparisonClass());
        }
    }
    else if((this->vectorKNN.size() == 0) || (distance <= this->vectorKNN.back().distanceFromRefPoint))
    {
        // Choose the first sub-tree to analyze

        switch(node->getSeparationAxis())
        {
            // If the bissectrice of the node is on x axis
            case separationIsOnX :
                if(refPoint->y() > node->point->y())
                {
                    firstSubTreeBefore = false;
                }
                break;
            // If the bissectrice of the node is on y axis
            case separationIsOnY :
                if(refPoint->x() > node->point->x())
                {
                    firstSubTreeBefore = false;
                }
                break;
            // If the bissectrice of the node is on z axis
            case separationIsOnZ :
                if(refPoint->z() > node->point->z())
                {
                    firstSubTreeBefore = false;
                }
                break;
            default :
                std::cerr << "[WARNING]: in kDTree, cannot determine axis of the node in function recursiveSearch_kNearestNeighbors" << std::endl;
                return;
        }

        if(firstSubTreeBefore)
        {
            this->recursiveSearch_kNearestNeighbors(refPoint, node->getFirstChild(), neighborsNumbers);
            this->recursiveSearch_kNearestNeighbors(refPoint, node->getSecondChild(), neighborsNumbers);
        }
        else
        {
            this->recursiveSearch_kNearestNeighbors(refPoint, node->getSecondChild(), neighborsNumbers);
            this->recursiveSearch_kNearestNeighbors(refPoint, node->getFirstChild(), neighborsNumbers);
        }
    }

    return;
}


// Methods


void kDTree::init(std::map<int, Vertex *, classComp> points)
{
    // Points list
    std::vector<Vertex*> pointsList;

    std::for_each(points.begin(), points.end(), [&pointsList](const std::map<int, Vertex *, classComp>::value_type& p) {pointsList.push_back(p.second);});

    this->init(pointsList);
}


void kDTree::init(std::vector<Vertex*> pointsList)
{
    // lists of points on each side of the bissectrice
    std::vector<Vertex*>firstPart;
    std::vector<Vertex*>secondPart;

    // Sort the points on x coordinates
    std::sort(pointsList.begin(), pointsList.end(), classCompOnX());

    // Separate the vector in twice to get sets of points on each side of the bissectrice
    firstPart = std::vector<Vertex*>(pointsList.begin(), pointsList.begin() + (pointsList.size()/2));
    secondPart = std::vector<Vertex*>((pointsList.begin() + (pointsList.size()/2))+1, pointsList.end());

    // Get bissectrice point
    this->isLeaf = false;
    this->point = firstPart.back();

    // Compute children
    this->firstChild = recursiveInitialization(firstPart, separationIsOnY);
    this->secondCHild = recursiveInitialization(secondPart, separationIsOnY);

    this->separationAxis = separationIsOnX;
    this->firstChild->setFather(this);
    this->secondCHild->setFather(this);
}


std::vector<Vertex*> kDTree::findKNN(const Vertex *refPoint, const unsigned int neighborsNumbers)
{
    this->vectorKNN = std::vector<Point>();
    std::vector<Vertex*> answVector;

    this->recursiveSearch_kNearestNeighbors(refPoint, this, neighborsNumbers);

    for(unsigned int i=0; i<this->vectorKNN.size(); i++)
    {
        answVector.push_back(this->vectorKNN[i].pt);
    }

    return answVector;
}


// Debugging methods

std::string kDTree::toString(int indent)
{
    std::string answ;
    for(int i=0; i<indent; i++)
    {
        answ += "\t";
    }

    if(this->isLeaf)
    {
        answ += "Leaf : (" + std::to_string(this->point->x()) + ", " + std::to_string(this->point->y()) + ", " + std::to_string(this->point->z()) + "), sep Axis : " + std::to_string(this->separationAxis) + "\n";
    }
    else
    {
        answ += "Root : (" + std::to_string(this->point->x()) + ", " + std::to_string(this->point->y()) + ", " + std::to_string(this->point->z()) + "), sep Axis : " + std::to_string(this->separationAxis) + "\n";
        if(this->firstChild != nullptr)
        {
            answ += this->firstChild->toString(++indent);
        }
        if(this->secondCHild != nullptr)
        {
            answ += this->secondCHild->toString(indent);
        }
    }

    return answ;
}










