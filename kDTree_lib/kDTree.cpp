#include "kDTree.h"


// Constructors and destructor

kDTree::kDTree()
{
}

kDTree::kDTree(Vertex *pt)
{
    this->firstChild = nullptr;
    this->secondCHild = nullptr;
    this->isLeaf = false;
    this->separationAxis = none;
    this->point = pt;
}


kDTree::kDTree(kDTree* firstChild, kDTree* secondCHild, Vertex* pt, enum enum_separationAxis sepAxis)
{
    this->firstChild = firstChild;
    this->secondCHild = secondCHild;
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














