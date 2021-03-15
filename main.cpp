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
          simHub.centra.at(i).vaccineren();
        }
        dag++;
    }
}


int main(int argc, char **argv) {

    // Inlezen
    Hub testhub;
    ProjectImporter p;
    p.importProject("../testInput/illegalSimulation2.xml", std::cout , testhub);
    std::cout << testhub.getTransport() << std::endl;



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

    for (unsigned int i = 0; i<H.centra.size(); i++){
        H.simuleerTransport(std::cout, H.centra[i]);
    }

    return 0;
}
