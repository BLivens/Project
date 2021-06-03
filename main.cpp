#include <iostream>
#include "HUB.h"
#include "ProjectImporter.h"
#include "ProjectExporter.h"



int main(int argc, char **argv) {

    Simulatie simulatie;
    // input
    ProjectImporter::importProject("../testInput/input.xml", std::cout , simulatie);

    //handmatige testcode voor input_2hubs_eenvoudig.xml
    /*
    std::cout << simulatie.hubs[0]->vaccins[0]->getType() << std::endl;
    std::cout << simulatie.hubs[0]->vaccins[1]->getType()<< std::endl;
    std::cout << simulatie.hubs[1]->vaccins[0]->getType()<< std::endl;
    std::cout << simulatie.hubs[1]->vaccins[1]->getType()<< std::endl;

    std::cout << (*simulatie.hubs[0]->centra[0])->getNaam() << std::endl;
    std::cout << (*simulatie.hubs[1]->centra[0])->getNaam() << std::endl;
    std::cout << (*simulatie.hubs[1]->centra[1])->getNaam() << std::endl;

    std::cout << (*simulatie.hubs[0]->centra[0])->vaccins[0]->getType() << std::endl;
    std::cout << (*simulatie.hubs[0]->centra[0])->vaccins[1]->getType() << std::endl;
    std::cout << (*simulatie.hubs[0]->centra[0])->vaccins[2]->getType() << std::endl;

    std::cout << (*simulatie.hubs[1]->centra[0])->vaccins[0]->getType() << std::endl;
    std::cout << (*simulatie.hubs[1]->centra[0])->vaccins[1]->getType() << std::endl;
    std::cout << (*simulatie.hubs[1]->centra[0])->vaccins[2]->getType() << std::endl;

    std::cout << (*simulatie.hubs[1]->centra[1])->vaccins[0]->getType() << std::endl;
    std::cout << (*simulatie.hubs[1]->centra[1])->vaccins[1]->getType() << std::endl;
    */
    // simuleren
    simulatie.simuleren(52, std::cout);
    // simpele uitvoer
    ProjectExporter::exportProject("output.txt", std::cout, (*simulatie.hubs[0]));
    // grafische weergave
    ProjectExporter::graphic_impression("output_grafische_weergave.txt", std::cout, (*simulatie.hubs[0]));
    return 0;
}
