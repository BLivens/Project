#include <iostream>
#include "HUB.h"
#include "ProjectImporter.h"
#include "ProjectExporter.h"



int main(int argc, char **argv) {

    Hub hub;
    // input
    ProjectImporter::importProject("../testInput/input.xml", std::cout , hub);
    // automatische simulatie
    hub.simuleren(3, std::cout);
    // output
    ProjectExporter::exportProject("output.txt", std::cout, hub);

    return 0;
}
