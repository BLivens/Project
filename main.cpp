#include <iostream>
#include "eigXML.h"
#include "HUB.h"
#include "ProjectImporter.h"



void simuleren(int dagen, Hub simHub) {
    int dag = 0;
    while (dag < dagen) {
        if (dag % simHub.getInterval() == 0) {
            simHub.verhoogVaccins(simHub.getTransport());
        }

        for (unsigned int i = 0; i<simHub.centra.size(); i++){
            simHub.simuleerTransport(std::cout, simHub.centra[i]);
        }

        for (unsigned int i = 0; i < simHub.centra.size(); i++) {
          simHub.centra.at(i)->vaccineren();
        }
        dag++;
    }
}

int main(int argc, char **argv) {

    // Inlezen
    Hub testhub;
    ProjectImporter::importProject("../testInput/input.xml", std::cout , testhub);
    std::cout << testhub.getTransport() << std::endl;
    for (unsigned int i = 0; i<testhub.centra.size(); i++){
        std::cout << testhub.centra[i]->getNaam() << std::endl;
    }
    /*

    Hub testhub2;
    Centrum* a;
    Centrum p;
    a = &p;
    Centrum* b;
    Centrum q;
    b = &q;
    a->setNaam("a");
    b->setNaam("b");
    testhub2.centra.push_back(a);
    testhub2.centra.push_back(b);
    std::cout << testhub2.centra[0]->getNaam()<< std::endl;
    std::cout << testhub2.centra[1]->getNaam() << std::endl;
    testhub2.centra[0]->setNaam("c");
    std::cout << p.getNaam()<< std::endl;
*/

/*
    // handmatig
    Centrum a;
    Centrum b;
    Centrum c;
    Centrum d;

    a.naam = "Park Spoor Oost";
    a.adres = "Noordersingel 40, Antwerpen";
    a.inwoners = 540173;
    a.capaciteit = 7500;
    a.vaccins = 0;

    b.naam = "AED Studios";
    b.adres = "Fabriekstraat 38, Lint";
    b.inwoners = 76935;
    b.capaciteit = 2000;
    b.vaccins = 0;

    c.naam = "De Zoerla";
    c.adres = "Gevaertlaan 1, Westerlo";
    c.inwoners = 49451;
    c.capaciteit = 1000;
    c.vaccins = 0;

    d.naam = "Flanders Expo";
    d.adres = "Maaltekouter 1, Sint-Denijs-Westrem";
    d.inwoners = 257029;
    d.capaciteit = 3000;
    d.vaccins = 0;

    Hub H;
    H.centra.push_back(a);
    H.centra.push_back(b);
    H.centra.push_back(c);
    H.centra.push_back(d);
    H.setTransport(2000);
    H.setInterval(6);
    H.setVaccins(93000);
    H.setLevering(93000);
    */
    /*
    for (unsigned int i = 0; i<testhub.centra.size(); i++){
        testhub.simuleerTransport(std::cout, testhub.centra[i]);
    }
    */
    return 0;
}
