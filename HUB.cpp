#include "HUB.h"

Hub::Hub(){
    _initCheck = this;
    transport = 0;
    vaccins.empty();
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
}

bool Hub::properlyInitialized() const{
    return _initCheck == this;
}
/*  Onhandig
std::vector<Vaccin> Hub::getVaccins() const{
    std::vector<Vaccin> result;
    REQUIRE(this->properlyInitialized(),
           "Hub wasn't initialized when calling getVaccins");
    result = vaccins;
    return result;
}

void Hub::setVaccins(std::vector<Vaccin> nieuwe_vaccins) {
    REQUIRE(this->properlyInitialized(),
            "Hub wasn't initialized when calling setVaccins");
    vaccins = nieuwe_vaccins;
    // ENSURE((getVaccins() == nieuwe_vaccins), "setVaccins postcondition failure"); TODO: Dit toch testen
}
*/

int Hub::getVoorraad() const {
    int result;
    REQUIRE(this->properlyInitialized(),
            "Hub wasn't initialized when calling getVoorraad");
    result = voorraad;
    return result;
}

void Hub::setVoorraad(int aantal_vaccins) {
    REQUIRE(this->properlyInitialized(),
            "Hub wasn't initialized when calling setVoorraad");
    voorraad = aantal_vaccins;
    ENSURE((getVoorraad() == aantal_vaccins), "setVoorraad postcondition failure");
}
/* Deze zijn niet meer nodig want worden nu afgehandeld door de vaccins
int Hub::getInterval() const{
    int result;
    REQUIRE(this->properlyInitialized(),
            "Hub wasn't initialized when calling getInterval");
    result = interval;
    ENSURE((result>0),"getInterval must return a strictly positive integer");
    return result;
}

void Hub::setInterval(int aantal_dagen) {
    REQUIRE(this->properlyInitialized(),
            "Hub wasn't initialized when calling setInterval");
    REQUIRE((aantal_dagen>0),
            "aantal_dagen must be a strictly positive integer");
    interval = aantal_dagen;
    ENSURE((getInterval() == aantal_dagen), "setInterval postcondition failure");
}
*/
int Hub::getTransport() const{
    int result = 0;
    REQUIRE(this->properlyInitialized(),
            "Hub wasn't initialized when calling getTransport");
    for (unsigned int i = 0; i < vaccins.size(); i++) {
        result+= vaccins[i]->getTransport();
    }
    ENSURE((result>0),"getTransport must return a strictly positive integer");
    return result;
}

void Hub::setTransport(int aantal_vaccins) {
    REQUIRE(this->properlyInitialized(),
            "Hub wasn't initialized when calling setTransport");
    REQUIRE((aantal_vaccins>0),
            "aantal_vaccins must be a strictly positive integer");
    transport = aantal_vaccins;
    ENSURE((getTransport() == aantal_vaccins), "setTransport postcondition failure");
}
/*
int Hub::getLevering() const{
    int result;
    REQUIRE(this->properlyInitialized(),
           "Hub wasn't initialized when calling getLevering");
    result = levering;
    ENSURE((result>=0),"getLevering must return a positive integer");
    return result;
}

void Hub::setLevering(int aantal_vaccins) {
    REQUIRE(this->properlyInitialized(),
            "Hub wasn't initialized when calling setLevering");
    REQUIRE((aantal_vaccins>=0),
            "aantal_vaccins must be a positive integer");
    levering = aantal_vaccins;
    ENSURE((getLevering() == aantal_vaccins), "setLevering postcondition failure");
}
*/
int Hub::berekenLadingen(const Centrum* centrum) const {
    REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling berekenLadingen");
    REQUIRE(centrum->properlyInitialized(), "Centrum wasn't initialized when calling berekenLadingen");
    REQUIRE(centrumVerbonden(centrum), "berekenLadingen requires centrum to be linked with Hub.");
    // declareer result
    int result;
    // indien er meer vaccins in het centrum aanwezig zijn dan de capaciteit van het centrum worden er geen result geleverd
    if (centrum->getCapaciteit() < centrum->getVoorraad()){
        result = 0;
    }
        // indien er wel result nodig zijn
    else{
        // bereken benodigde result
        int nodige_ladingen = (centrum->getCapaciteit() - centrum->getVoorraad())/getTransport();
        if ((centrum->getCapaciteit() - centrum->getVoorraad())%getTransport() != 0){
            nodige_ladingen = nodige_ladingen + 1;
        }
        // bereken het maximaal aantal result dat het centrum kan ontvangen
        int max_ladingen = (centrum->getCapaciteit()*2 - centrum->getVoorraad())/getTransport();
        // bereken het aantal beschikbare result in de Hub
        int beschikbare_ladingen = getVoorraad()/getTransport();
        // Indien er minder result beschikbaar zijn dan geleverd moeten worden
        if (beschikbare_ladingen<nodige_ladingen){
            // lever alle result die in de Hub aanwezig zijn
            result = beschikbare_ladingen;
        }
            // anders als de result zo groot zijn dat het max aantal result overschreden worden
        else if (nodige_ladingen>max_ladingen){
            // er wordt niets geleverd
            result = 0;
        }
            // anders is het aantal result gelijk aan de benodigde result
        else {
            result = nodige_ladingen;
        }
    }
    ENSURE(result >= 0, "berekenLadingen must return a positive integer");
    return result;
}



void Hub::simuleerTransport(std::ostream &onStream, Centrum* centrum) {
    REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling berekenLadingen");
    REQUIRE(centrum->properlyInitialized(), "Centrum wasn't initialized when calling simuleerTransport");
    REQUIRE(centrumVerbonden(centrum), "simuleerTransport requires centrum to be linked with Hub.");
    /*
    // bereken aantal ladingen
    int aantal_ladingen = berekenLadingen(centrum);
    // bereken aantal vaccins
    int aantal_vaccins = aantal_ladingen * getTransport();
    // verlaag het aantal vaccins in de Hub met de correcte hoeveelheid
    setVoorraad(getVoorraad() - aantal_vaccins); // TODO: In verdere iteraties moeten de vaccins van het juiste type verdwijnen.
    // verhoog het aantal vaccins in het centrum met de correcte hoeveelheid
    centrum->setVoorraad(centrum->getVoorraad() + aantal_vaccins);
    // schrijf overzicht uit
    */
    int aantal_ladingen = 0;
    int aantal_vaccins = 0;
    for (unsigned int i = 0; i  < vaccins.size(); i++){
        int result = 0;
        if (centrum->getCapaciteit() < centrum->getVoorraad()){
            result = 0;
        }
            // indien er wel result nodig zijn
        else{
            // bereken benodigde result
            int nodige_ladingen = (centrum->getCapaciteit() - centrum->getVoorraad())/vaccins[i]->getTransport();
            if ((centrum->getCapaciteit() - centrum->getVoorraad())%vaccins[i]->getTransport() != 0){
                nodige_ladingen = nodige_ladingen + 1;
            }
            // bereken het maximaal aantal result dat het centrum kan ontvangen
            int max_ladingen = (centrum->getCapaciteit()*2 - centrum->getVoorraad())/vaccins[i]->getTransport();
            // bereken het aantal beschikbare result in de Hub
            int beschikbare_ladingen = vaccins[i]->getVoorraad()/vaccins[i]->getTransport();
            // Indien er minder result beschikbaar zijn dan geleverd moeten worden
            if (beschikbare_ladingen<nodige_ladingen){
                // lever alle result die in de Hub aanwezig zijn
                result = beschikbare_ladingen;
            }
                // anders als de result zo groot zijn dat het max aantal result overschreden worden
            else if (nodige_ladingen>max_ladingen){
                // er wordt niets geleverd
                result = 0;
            }
                // anders is het aantal result gelijk aan de benodigde result
            else {
                result = nodige_ladingen;
            }
        }
        vaccins[i]->setVoorraad(vaccins[i]->getVoorraad()-result*vaccins[i]->getTransport());
        centrum->vaccins[i].setVoorraad(centrum->vaccins[i].getVoorraad()+result*vaccins[i]->getTransport());
        aantal_ladingen = aantal_ladingen + result;
        aantal_vaccins = aantal_vaccins + result * vaccins[i]->getTransport();
    }
    onStream << "Er werden " << aantal_ladingen << " ladingen ("<< aantal_vaccins <<" vaccins) getransporteerd naar " << centrum->getNaam()<< "." <<std::endl;
}


bool Hub::centrumVerbonden(const Centrum* centrum) const{
    REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling centrumVerbonden");
    REQUIRE(centrum->properlyInitialized(), "Centrum wasn't initialized when calling centrumVerbonden");
    bool isVerbonden = false;
    for (unsigned int i = 0; i<centra.size(); i++){
        if(centrum->getNaam() == centra[i]->getNaam() and centrum->getAdres() == centra[i]->getAdres()){
            isVerbonden = true;
        }
    }
    return isVerbonden;
}

void Hub::simuleren(int dagen, std::ostream &onStream) {
    REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling simuleren");
    REQUIRE(dagen>=0, "Dagen must be an integer greater or equal to 0.");
    int dag = 0;
    while (dag < dagen) {
        for (unsigned int i = 0; i < vaccins.size(); i++) {
            if (dag % vaccins[i]->getInterval() == 0) {
                int plus = vaccins[i]->getLevering();
                setVoorraad(getVoorraad() + plus);
                vaccins[i]->setVoorraad(vaccins[i]->getVoorraad() + plus);
            }
        }
        for (unsigned int i = 0; i<centra.size(); i++){
            simuleerTransport(onStream,centra[i]);
        }

        for (unsigned int i = 0; i < centra.size(); i++) {
            centra.at(i)->vaccineren(onStream, dag);
        }
        dag++;
    }
}
