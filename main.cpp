#include <iostream>
#include "HUB.h"
#include "ProjectImporter.h"
#include "ProjectExporter.h"



int main(int argc, char **argv) {

    Hub hub;
    // input
    ProjectImporter::importProject("../testInput/input.xml", std::cout , hub);
    // simuleren
    hub.simuleren(52, std::cout);
    // simpele uitvoer
    ProjectExporter::exportProject("output.txt", std::cout, hub);
    // grafische weergave
    ProjectExporter::graphic_impression("output_grafische_weergave.txt", std::cout, hub);
    return 0;
}
