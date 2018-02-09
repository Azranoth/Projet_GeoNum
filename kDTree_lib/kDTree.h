#ifndef __KDTREE_H
#define __KDTREE_H


#include "mesh.h"


enum enum_separationAxis {separationIsOnX, separationIsOnY, separationIsOnZ, none};

/**
 * @brief The kDTree class represents the kDTree object with k = 2
 */
class kDTree
{
// Attributes
private:
    kDTree* firstChild;
    kDTree* secondCHild;
    bool isLeaf;
    enum enum_separationAxis separationAxis;
    /// Point coordinates or point of the bissectrice
    Vertex* point;


// Construtors and destructor
public:

    kDTree();

    /**
     * @brief kDTree constructor for a leaf node
     * @param firstChild
     * @param secondCHild
     * @param pt
     */
    kDTree(Vertex* pt);

    /**
     * @brief kDTree Constructor for non-leaf node
     * @param firstChild
     * @param secondCHild
     * @param pt
     * @param sepAxis
     */
    kDTree(kDTree* firstChild, kDTree* secondCHild, Vertex* pt, enum_separationAxis sepAxis);

    ~kDTree();

// Getters and setters
public:

    kDTree* getFirstChild();

    void setFirstChild(kDTree* newNode);

    kDTree* getSecondChild();

    void setSecondChild();

    bool isLeafNode() const;

    void isLeafNode(bool newValue);

    Vertex* getPoint();

    void setPoint(Vertex* point);

// Auxiliary methods
private:

    kDTree* recursiveInitialization(std::vector<kDTree*> pointsList, int divisionAxis);


// Methods
public:

    void init(std::map<int, Vertex*, classComp> points);

};


#endif

