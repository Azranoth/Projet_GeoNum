
#include "PlanesGraph.h"


// ----- Constructors
PlanesGraph::PlanesGraph(){
    this->_listOfNodes = std::map<int, Node*, classCompNodes>();
}

PlanesGraph::PlanesGraph(std::map<int, Node*, classCompNodes> map){
    this->_listOfNodes = map;
}

PlanesGraph::PlanesGraph(std::vector<Plane*> planes){

    this->_listOfNodes = std::map<int, Node*, classCompNodes>();
    std::vector<Plane*>::iterator itP;

    for(itP = planes.begin(); itP != planes.end(); ++itP){

        this->_listOfNodes.insert(std::make_pair( (*itP)->center()->getId(), new Node((*itP)->normal(), (*itP)->center() ) ));
    }
}

// ----- Methods
void PlanesGraph::display(){
    std::map<int, Node*, classCompNodes>::iterator itNodes;
    std::cout << "GRAPH : " << std::endl;
    for(itNodes = this->_listOfNodes.begin(); itNodes != this->_listOfNodes.end(); ++itNodes){
        std::cout << "--";
        (*itNodes).second->display();
    }
}


void PlanesGraph::addNode(Node *n){
    this->_listOfNodes.insert(std::make_pair( n->getCenter()->getId(), n ));
}



std::vector<Plane*> PlanesGraph::kruskal(){

    // Create temporary types specifically to use Boost's Kruskal algorithm
    typedef adjacency_list < vecS, vecS, undirectedS,no_property, property < edge_weight_t, int > > Graph;
    typedef graph_traits < Graph >::edge_descriptor BEdge;
    typedef std::pair<int, int> E;

    std::map<int, Node*, classCompNodes>::iterator it;
    std::map<int, Edge*, classCompEdges>::iterator itE;

    // Get number of nodes in the graph
    const int num_nodes = this->_listOfNodes.size();

    // Get number of edges
    int num_edges = 0;
    for(it = this->_listOfNodes.begin(); it != this->_listOfNodes.end(); it++){

        num_edges = num_edges + (*it).second->getEdges().size();
    }
    // Boost's Kruskal MST require edges stored as a (int, int) array & corresponding weights as an int array
    E edge_array[num_edges];
    int weights[num_edges];
    int i = 0;

    for(it = this->_listOfNodes.begin(); it != this->_listOfNodes.end(); it++){

        for(itE = (*it).second->getEdges().begin(); itE != (*it).second->getEdges().end(); itE++){

            edge_array[i] = E( (*itE).second->getSrcPlane()->getCenter()->getId(), (*itE).second->getTargetPlane()->getCenter()->getId() );
            weights[i]  = (*itE).second->getWeight();

            i++;
        }
    }

/*    for(int i = 0; i < sizeof(edge_array)/sizeof(E); i++){
        std::cout << "(" << edge_array[i].first << "," << edge_array[i].second << ") of weight " << weights[i] << std::endl;
    }*/

    Graph g(edge_array, edge_array + num_edges, weights, num_nodes);
    property_map < Graph, edge_weight_t >::type weight = get(edge_weight, g);
    std::vector < BEdge > spanning_tree;
    // Apply Kruskal MST algorithm on the arrays and get the MST in spanning_tree variable
    kruskal_minimum_spanning_tree(g, std::back_inserter(spanning_tree));


    //Create a new graph object with every nodes but only containing MST's edges
    std::vector<BEdge>::iterator itBE;
    std::map<int, Node*, classCompNodes>::iterator n, n2;
    std::map<int, Node*, classCompNodes> newNodes = std::map<int, Node*, classCompNodes>();
    Node *newSrc, *newTarget;
    Vector3d newNormalSrc, newNormalTarget;
    Vertex *newCenterSrc, *newCenterTarget;

    for(itBE = spanning_tree.begin(); itBE != spanning_tree.end(); itBE++){

        //----- Edge's source
        n = this->_listOfNodes.find( source(*itBE, g) );

        newNormalSrc = (*n).second->getNormal();
        newCenterSrc = (*n).second->getCenter();

        newSrc = new Node(newNormalSrc, newCenterSrc);

        //----- Edge's target
        n = this->_listOfNodes.find( target(*itBE, g) );

        newNormalTarget  = (*n).second->getNormal();
        newCenterTarget  = (*n).second->getCenter();

        newTarget = new Node(newNormalTarget, newCenterTarget);

        n  = newNodes.find( newSrc->getCenter()->getId() );
        n2 = newNodes.find( newTarget->getCenter()->getId() );

        // If both source & target nodes are already in the map then add the edges directly
        if( n != newNodes.end() && n2 != newNodes.end() ){
            (*n).second->addEdge(newTarget, weight[*itBE]);
            (*n2).second->addEdgePointingToThisPlane(newSrc, weight[*itBE]);
        }
        else{

            // Else make sure that they are both inserted in
            if(n == newNodes.end() ){
                newNodes.insert( std::make_pair(newSrc->getCenter()->getId()   , newSrc   ) );
            }
            if(n2 == newNodes.end()){
                newNodes.insert( std::make_pair(newTarget->getCenter()->getId(), newTarget) );
            }
            // Then add the edges
            n  = newNodes.find( newSrc->getCenter()->getId() );
            (*n).second->addEdge(newTarget, weight[*itBE]);
            n2 = newNodes.find( newTarget->getCenter()->getId() );
            (*n2).second->addEdgePointingToThisPlane(newSrc, weight[*itBE]);

        }

    }

    // Planes orientation propagation
    // ------ Assigning orientation to the initial plane with the largest Z coordinate
    Node* maxZPlane = (*newNodes.begin()).second;
    std::map<int, Node*, classCompNodes>::iterator itNodes;
    for(itNodes = newNodes.begin(); itNodes != newNodes.end(); ++itNodes){
        ///(*itNodes).second->display();
        if((*itNodes).second->getCenter()->z() > maxZPlane->getCenter()->z() ){
            maxZPlane = (*itNodes).second;
        }
    }

    if( maxZPlane->getNormal()(2) < 0){
        (*newNodes.find( maxZPlane->getCenter()->getId() )).second->setNormal( -maxZPlane->getNormal() );
    }

    // ------ Propagate the orientation recursively
    newNodes[maxZPlane->getCenter()->getId()]->orientNormalsMap(newNodes, -1);

    // Return the list of rightly oriented planes as a vector of Plane objects
    std::vector<Plane*> newPlanes;
    for(itNodes = newNodes.begin(); itNodes != newNodes.end(); ++itNodes){
        newPlanes.push_back( (*itNodes).second->getPlane() );
    }
    return newPlanes;
}
