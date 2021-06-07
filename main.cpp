#include <iostream>
#include "HUB.h"
#include "ProjectImporter.h"
#include "ProjectExporter.h"



int main(int argc, char **argv) {

    Simulatie simulatie;

    ProjectImporter::importProject("../testInput/input.xml", std::cout, simulatie);

    // simuleren
    simulatie.simuleren(52, std::cout);
    // simpele uitvoer
    ProjectExporter::exportProject("output.txt", std::cout, (*simulatie.hubs[0]));
    // grafische weergave
    ProjectExporter::graphic_impression("output_grafische_weergave.txt", std::cout, (*simulatie.hubs[0]));
    // statistische weergave
    ProjectExporter::statistics("output_statistics.txt", std::cout, simulatie);

    return 0;
}
