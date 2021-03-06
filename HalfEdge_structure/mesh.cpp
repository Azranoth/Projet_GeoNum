#include "mesh.h"

Mesh::Mesh()
{
    this->kd_tree = nullptr;
    this->_vertices = std::map<int, Vertex*, classComp>();
    this->_faces = std::map<int, Face*, classComp>();
}

Mesh::Mesh(std::map<int, Vertex *, classComp> vertices)
{
    this->kd_tree = nullptr;
    this->_vertices = vertices;
    this->_faces = std::map<int, Face*, classComp>();
}

Mesh::Mesh(std::map<int, Face*, classComp> faces)
{
    this->kd_tree = nullptr;
    this->_vertices = std::map<int, Vertex*, classComp>();
    this->_faces = faces;
}

Mesh::Mesh(std::map<int, Vertex *, classComp> vertices, std::map<int, Face *, classComp> faces)
{
    this->kd_tree = nullptr;
    this->_vertices = vertices;
    this->_faces = faces;
}

void Mesh::addVertex(Vertex* v){
    this->_vertices.insert(std::make_pair(v->getId(), v));
}

void Mesh::addFace(Face* f){
    this->_faces.insert(std::make_pair(f->getId(), f));
}

void Mesh::addEdge(HalfEdge* he){
    this->_edges.insert(std::make_pair(std::make_pair(he->getSourceVertex()->getId(), he->getNextHalfEdge()->getSourceVertex()->getId()), he));
}

void Mesh::display(){
    std::cout << "-------------- MESH : " << std::endl;
    std::map<int, Face*>::iterator it;
    for(it = this->_faces.begin(); it != this->_faces.end(); it++){
        (*it).second->display();
    }
}

void Mesh::verticesDisplay(){
    std::cout << "------- MESH (VERTICES): " << std::endl;
    std::map<int, Vertex*>::iterator it;
    for(it = this->_vertices.begin(); it != this->_vertices.end(); it++){
        (*it).second->display();
    }
}

void Mesh::importOFF(const char* filename){

    std::cout << "Starting importation of " << filename << "..." << std::endl;
    std::ifstream is;
    is.open(filename);

    if(!is.is_open())
    {
        std::cerr << "[WARNING]: in importOFF in Mesh class, cannot open " << filename << std::endl;
    }

    // Get file's length
    is.seekg(0, is.end);
    int length = is.tellg();
    is.seekg(0, is.beg);

    char* buffer = new char[length];
    // Fill buffer
    is.read(buffer, length);
    is.close();

    std::stringstream stream;
    stream.str(buffer);
    delete[] buffer;

    std::string str;
    std::getline(stream, str);
    if (str != "OFF") {
        std::cerr << "Bad format " << str << std::endl;
        exit(1);
    }
    // Ignore comments
    std::getline(stream, str);
    while (str[0] == '#') {
        std::getline(stream, str);
    }

    int nbVertices, nbFaces, nbEdges;
    std::stringstream ss;
    ss.str(str);
    ss >> nbVertices;
    ss >> nbFaces;
    ss >> nbEdges;
    std::cout << "Getting " << nbVertices << " vertices, " << nbFaces << " faces, " << nbEdges << " edges." << std::endl;
    double x, y, z;
    // Get OFF file's vertices
    for(int i = 0; i < nbVertices; i++){
        stream >> x; stream >> y; stream >> z;
        this->addVertex(new Vertex(x,y,z));
    }

    // If we are loading a points cloud
    if(nbFaces == 0)
    {
        std::cout << "Loading a mesh from a points cloud..." << std::endl;
        // Lazy memory allocation
        this->kd_tree = new kDTree();
        this->kd_tree->init(this->_vertices);
        return;
    }
    // If we are loading a mesh
    else
    {
        // Get OFF file's faces
        int verticesPerFace;
        int idx;
        for(int i = 0; i < nbFaces; i++){
            std::cout << "Processing face number " << i <<"..." << std::endl;
            stream >> verticesPerFace;
            if (verticesPerFace <= 2) {
                std::cerr << "Bad format : vertices per face " << str << std::endl;
                exit(1);
            }

            // First half-edge & creation of the face
            stream >> idx;
            std::map<int, Vertex*>::iterator it;
            it = this->_vertices.find(idx);
            if(it == this->_vertices.end()){
                std::cerr << "Bad vertex index - closing the program" << std::endl;
            }
            HalfEdge* firstHEdgeOfFace = new HalfEdge((*it).second);

            if((*it).second->getChildEdge() != NULL)
                (*it).second->setChildEdge(firstHEdgeOfFace);

            Face* newFace = new Face(firstHEdgeOfFace);
            newFace->setNbVertices(verticesPerFace);
            firstHEdgeOfFace->setFace(newFace);

            // Second half-edge of the face
            stream >> idx;
            it = this->_vertices.find(idx);
            if(it == this->_vertices.end()){
                std::cerr << "Bad vertex index - closing the program" << std::endl;
            }

            HalfEdge* newHEdgeOfFace = new HalfEdge((*it).second);
            firstHEdgeOfFace->setNextHalfEdge(newHEdgeOfFace);
            this->addEdge(firstHEdgeOfFace);
            newHEdgeOfFace->setPrevHalfEdge(firstHEdgeOfFace);

            if((*it).second->getChildEdge() == NULL)
                (*it).second->setChildEdge(newHEdgeOfFace);
            newHEdgeOfFace->setFace(newFace);

            // Each following half-edge of the face
            HalfEdge* prevHE = newHEdgeOfFace;
            for(int j = 2; j < verticesPerFace; j++){

                stream >> idx;
                it = this->_vertices.find(idx);
                if(it == this->_vertices.end()){
                    std::cerr << "Bad vertex index - closing the program" << std::endl;
                }

                HalfEdge* newHE = new HalfEdge((*it).second);
                newHE->setFace(newFace);
                prevHE->setNextHalfEdge(newHE);
                this->addEdge(prevHE);
                newHE->setPrevHalfEdge(prevHE);

                prevHE = newHE;
                if((*it).second->getChildEdge() == NULL)
                    (*it).second->setChildEdge(newHE);
            }
            // Close the face
            prevHE->setNextHalfEdge(firstHEdgeOfFace);
            this->addEdge(prevHE);
            firstHEdgeOfFace->setPrevHalfEdge(prevHE);
            // And insert it DEEPLY into the map.
            if(newFace->getHalfEdge() != NULL)
                this->addFace(newFace);
        }

        // Set teteBeche half edge for each half edge of the mesh
        std::map<std::pair<int, int>, HalfEdge*>::iterator it;
        std::map<std::pair<int, int>, HalfEdge*>::iterator itHE;
        for(it = this->_edges.begin(); it != this->_edges.end(); it++){

            itHE = this->_edges.find(std::make_pair( (*it).second->getNextHalfEdge()->getSourceVertex()->getId(),
                                                     (*it).second->getSourceVertex()->getId()) );
            (*it).second->setTeteBeche( (*itHE).second );
            (*itHE).second->setTeteBeche( (*it).second );
        }
    }
    std::cout << " size of the faces list    : " << this->_faces.size() << std::endl;
    std::cout << " size of the vertices list : " << this->_vertices.size() << std::endl;

}

void Mesh::importOFF(const std::string fileName)
{
    this->importOFF(fileName.c_str());
}

void Mesh::exportOFF(const char *filename){

    // Creating the OFF file where the mesh is to be exported
    std::ofstream fs(filename);
    if(!fs){
        std::cerr << "Cannot create OFF file" << std::endl;
    }

    // Write header in it
    fs << "OFF\n";
    fs << this->_vertices.size() << " " << this->_faces.size() << " 0\n";


    // Write vertices coordinates in it
    std::map<int, Vertex*>::iterator it;
    for(it=this->_vertices.begin(); it != this->_vertices.end(); it++){
        fs << (*it).second->x() << " " << (*it).second->y() << " " << (*it).second->z() << "\n";
    }

    // Write faces vertices composition in it
    std::map<int, Face*>::iterator itF;
    // For each face of the mesh :
    for(itF=this->_faces.begin(); itF != this->_faces.end(); itF++){
        fs << (*itF).second->getNbVertices() << "  ";
        // Process face first half-edge's following half-edges until we fall back on the first one
        // and write in file the source vertex's id of each half-edge
        HalfEdge* temp = (*itF).second->getHalfEdge();
        fs << temp->getSourceVertex()->getId();

        temp = temp->getNextHalfEdge();
        while(temp != (*itF).second->getHalfEdge()){
            fs << " " << temp->getSourceVertex()->getId();
            temp = temp->getNextHalfEdge();
        }
        fs << "\n";
    }

    // Close the file
    fs.close();
}

void Mesh::exportOFF(const std::__cxx11::string fileName)
{
    this->exportOFF(fileName.c_str());
}

