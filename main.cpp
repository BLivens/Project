#include <iostream>
#include "HUB.h"
#include "ProjectImporter.h"
#include "ProjectExporter.h"



int main(int argc, char **argv) {

    Hub hub;
    // input
    ProjectImporter::importProject("../testInput/input.xml", std::cout , hub);

/* Hanmatige test Importer
    for (unsigned int i = 0; i < hub.vaccins.size(); i++){
        std::cout << hub.vaccins[i]->getType() << std::endl;
        std::cout << hub.vaccins[i]->getLevering()<< std::endl;
        std::cout << hub.vaccins[i]->getInterval() << std::endl;
        std::cout << hub.vaccins[i]->getTransport() << std::endl;
        std::cout << hub.vaccins[i]->getHernieuwing() << std::endl;
        std::cout << hub.vaccins[i]->getTemperatuur() << std::endl;
    }

    std::cout << hub.centra[1]->getNaam() << std::endl;
    std::cout << hub.centra[1]->getAdres()<< std::endl;
    std::cout << hub.centra[1]->getInwoners()<< std::endl;
    std::cout << hub.centra[1]->getCapaciteit() << std::endl;
    std::cout << hub.centra[1]->vaccins[0].getType()<< std::endl;
    std::cout << hub.centra[1]->vaccins[0].getHernieuwing()<< std::endl;
    std::cout << hub.centra[1]->vaccins[0].getVoorraad()<< std::endl;

    std::cout << hub.centra[1]->vaccins[1].getType()<< std::endl;
    std::cout << hub.centra[1]->vaccins[1].getHernieuwing()<< std::endl;
    std::cout << hub.centra[1]->vaccins[1].getVoorraad()<< std::endl;

    hub.vaccins[0]->setVoorraad(93000);
    hub.simuleerTransport(std::cout, hub.centra[0]);
    std::cout << hub.vaccins[0]->getVoorraad();
    std::cout << hub.centra[0]->vaccins[0].getVoorraad();
    */
    // automatische simulatie
    hub.simuleren(12, std::cout);
    // output

    ProjectExporter::exportProject("output.txt", std::cout, hub);
    ProjectExporter::graphic_impression("output_grafische_weergave.txt", std::cout, hub);

    return 0;
}
