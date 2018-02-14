#ifndef __KDTREE_H
#define __KDTREE_H


#include <algorithm>
#include "mesh.h"

//class Mesh;
struct classComp;

enum enum_separationAxis {separationIsOnX, separationIsOnY, separationIsOnZ, none};

struct classCompOnX
{
    bool operator() (Vertex* v1, Vertex* v2) const
    { return v1->x()<v2->x(); }
};

struct classCompOnY
{
    bool operator() (Vertex* v1, Vertex* v2) const
    { return v1->y()<v2->y(); }
};

struct classCompOnZ
{
    bool operator() (Vertex* v1, Vertex* v2) const
    { return v1->z()<v2->z(); }
};

struct Point
{
    Vertex* pt;
    float distanceFromRefPoint;

    Point() {}
};

struct pointComparisonClass
{
    bool operator() (const Point& p1, const Point& p2) const
    { return p1.distanceFromRefPoint <= p2.distanceFromRefPoint; }
};

/**
 * @brief The kDTree class represents the kDTree object with k = 2
 */
class kDTree
{
// Attributes
private:
    kDTree* father;
    kDTree* firstChild;
    kDTree* secondCHild;
    bool isLeaf;
    enum enum_separationAxis separationAxis;
    /// Point coordinates or point of the bissectrice
    Vertex* point;

// Attributes used for internal computations
private:
    /// Vector of Point elements
    std::vector<Point> vectorKNN;


// Construtors and destructor
public:

    kDTree();

    /**
     * @brief kDTree constructor for a leaf node
     * @param father father node
     * @param pt vertex in the node
     */
    kDTree(kDTree *father, Vertex* pt);

    /**
     * @brief kDTree Constructor for non-leaf node
     * @param father father node
     * @param firstChild
     * @param secondCHild
     * @param pt point representing the bissectrice between the children
     * @param sepAxis axis of the bissectrice
     */
    kDTree(kDTree* father, kDTree* firstChild, kDTree* secondCHild, Vertex* pt, enum_separationAxis sepAxis);

    ~kDTree();

// Getters and setters
public:


    /**
     * @brief getFather getter for the father of the node
     * @return
     */
    kDTree* getFather();


    /**
     * @brief setFather setter of the father of the node
     * @param newFather
     */
    void setFather(kDTree* newFather);


    /**
     * @brief getFirstChild getter for the first child
     * @return
     */
    kDTree* getFirstChild();


    /**
     * @brief setFirstChild setter for the first child
     * @param newNode
     */
    void setFirstChild(kDTree* newNode);


    /**
     * @brief getSecondChild getter for the second child
     * @return
     */
    kDTree* getSecondChild();


    /**
     * @brief setSecondChild setter for the second child
     * @param newNode
     */
    void setSecondChild(kDTree* newNode);


    /**
     * @brief isLeafNode return true if the node is a leaf
     * @return
     */
    bool isLeafNode() const;


    /**
     * @brief isLeafNode set if the node is a leaf or not
     * @param newValue
     */
    void isLeafNode(bool newValue);


    /**
     * @brief getPoint getter for the point of the node
     * @return
     */
    Vertex* getPoint();


    /**
     * @brief setPoint setter for the point of the node
     * @param point
     */
    void setPoint(Vertex* point);


    /**
     * @brief getSeparationAxis return the separation axis of the node
     * @return
     */
    enum enum_separationAxis getSeparationAxis();

// Auxiliary methods
private:


    /**
     * @brief recursiveInitialization used to build the tree
     * @param pointsList
     * @param divisionAxis
     * @return
     */
    kDTree* recursiveInitialization(std::vector<Vertex *> pointsList, enum_separationAxis divisionAxis);


    /**
     * @brief bissectricePoint find the point between two given points
     * @param v1
     * @param v2
     * @return
     */
    Vertex* bissectricePoint(Vertex* v1, Vertex* v2);


    /**
     * @brief euclideanDistance compute the euclidean distance
     * @param v1
     * @param v2
     * @return
     */
    float euclideanDistance(const Vertex* v1, const Vertex* v2) const;


    /**
     * @brief recursiveSearch_kNearestNeighbors recursive method to find the k Nearest Neighbors
     * @param node
     * @param neighborsNumbers
     */
    void recursiveSearch_kNearestNeighbors(const Vertex* refPoint, kDTree* node, const unsigned int neighborsNumbers);


// Methods
public:


    /**
     * @brief init Tree initialization
     * @param points
     */
    void init(std::map<int, Vertex*, classComp> points);


    /**
     * @brief findKNN find the k Nearest Neighbors of the given point
     * @param refPoint
     * @param neighborsNumbers
     * @return
     */
    std::vector<Vertex*> findKNN(const Vertex* refPoint, const unsigned int neighborsNumbers);


// Debugging methods
public:


    /**
     * @brief toString return the string version of the tree
     * @return
     */
    std::string toString(int indent);

};

inline std::ostream& operator<<(std::ostream& os, kDTree& obj)
{
    os << obj.toString(0);
    return os;
}

inline std::ostream& operator<<(std::ostream& os, kDTree* obj)
{
    os << obj->toString(0);
    return os;
}


#endif

