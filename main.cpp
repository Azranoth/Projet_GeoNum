#include <QCoreApplication>

#include "mesh.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    char* filename = "../OFF/almost_torus.off";
    Mesh mesh = Mesh();
    mesh.importOFF(filename);
    mesh.exportOFF("../OFF/export_test.off");
    mesh.display();

    return a.exec();
}

