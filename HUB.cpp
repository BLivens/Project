#include "HUB.h"

Hub::Hub(){
    _initCheck = this;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
}

bool Hub::properlyInitialized() const{
    return _initCheck == this;
}

int Hub::getVoorraad() const {
    int result = 0;
    REQUIRE(this->properlyInitialized(),
            "Hub wasn't initialized when calling getVoorraad");
    for (unsigned int i = 0; i < vaccins.size(); i++){
        result = result + vaccins[i]->getVoorraad();
    }
    ENSURE((result>=0), "getVoorraad must return a positive integer");
    return result;
}


void Hub::simuleerTransport(std::ostream &onStream, Centrum* centrum) {
    REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling simuleerTransport");
    REQUIRE(centrum->properlyInitialized(), "Centrum wasn't initialized when calling simuleerTransport");
    REQUIRE(centrumVerbonden(centrum), "simuleerTransport requires centrum to be linked with Hub.");

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
        centrum->vaccins[i]->setVoorraad(centrum->vaccins[i]->getVoorraad()+result*vaccins[i]->getTransport());
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
