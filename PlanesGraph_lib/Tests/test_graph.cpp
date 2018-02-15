
#include "PlanesGraph.h"


int main(int argc, char *argv[]) {


    PlanesGraph g = PlanesGraph();

    Vertex *v0 = new Vertex(4, 3, 1);
    Vertex *v1 = new Vertex(6, 5, 2);
    Vertex *v2 = new Vertex(6, 2, 3);
    Vertex *v3 = new Vertex(4, 0, 1);
    Vertex *v4 = new Vertex(1, 1, 0);

    Node* n0 = new Node(v0);
    Node* n1 = new Node(v1);
    Node* n2 = new Node(v2);
    Node* n3 = new Node(v3);
    Node* n4 = new Node(v4);

    n0->addEdge(n2, 1.);
    n1->addEdge(n3, 1.);
    n1->addEdge(n4, 2.);
    n2->addEdge(n1, 7.);
    n2->addEdge(n3, 3.);
    n3->addEdge(n4, 1.);
    n4->addEdge(n0, 1.);
    n4->addEdge(n1, 1.);


    n2->addEdge(n0, 1.);
    n3->addEdge(n1, 1.);
    n4->addEdge(n1, 2.);
    n1->addEdge(n2, 7.);
    n3->addEdge(n2, 3.);
    n4->addEdge(n3, 1.);
    n0->addEdge(n4, 1.);
    n1->addEdge(n4, 1.);

    g.addNode(n0);
    g.addNode(n1);
    g.addNode(n2);
    g.addNode(n3);
    g.addNode(n4);

    PlanesGraph* g2 = g.kruskal();

    g2->display();


    return 0;
}
