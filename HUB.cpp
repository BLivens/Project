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


void Hub::simuleerTransport(std::ostream &onStream, int dag){
    REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling simuleerTransport");
    REQUIRE(dag >= 0, "Dag must be a non-negative number when calling simuleerTransport");


    std::vector<int> tot_lading(centra.size(), 0);
    std::vector<int> tot_vacs(centra.size(), 0);
    std::vector<int> dringende(centra.size(), 0);

    for (unsigned int i = 0; i < vaccins.size(); i++) {
        std::vector<int>levvac(centra.size(), 0);

        std::string type = vaccins[i]->getType();
        int tweedeDosis;

        for (unsigned int j = 0; j < centra.size(); j++) { // de loop van de eerste kans, voor tweed prikken
            tweedeDosis = std::max(0, (*centra[j])->getTweedes(dag, type) - (*centra[j])->vaccins[i]->getVoorraad()); // dit is hoeveel het centrum tekort komt, hopelijk kunnen we het sturen

            if (tweedeDosis <= vaccins[i]->getVoorraad()) { // we hebben genoeg op voorhand voor de tweede prikken, gelukkig!
                vaccins[i]->setVoorraad(vaccins[i]->getVoorraad() - tweedeDosis);
                dringende[j] += tweedeDosis;
                levvac[j] += tweedeDosis;
            } else { // oei, tekort :( we sturen alles dat we kunnen
                dringende[j] += vaccins[i]->getVoorraad();
                levvac[j] += vaccins[i]->getVoorraad();
                vaccins[i]->setVoorraad(0);
            }
        }

        double wachttijd = dag % vaccins[i]->getInterval() + 1;
        double doel = (vaccins[i]->getVoorraad()/wachttijd)/centra.size();

        for (unsigned int j = 0; j < centra.size(); j++) { // de loop van de tweede kans
            double zending;
            if ((*centra[j])->getCapaciteit()*2 - (*centra[j])->getVoorraad() <= doel + dringende[j]) { // het minumum van wat we willen sturen en wat we kunnen sturen
                zending = (*centra[j])->getCapaciteit()*2 - (*centra[j])->getVoorraad();
            } else {
                zending = doel;
            }
            if (vaccins[i]->getTemperatuur() < 0) {
                zending = std::min(zending, (double)((*centra[j])->getCapaciteit() - dringende[j])); // als het dezelfde dag nog geprikt moet worden kunnen we er misschien maar minder sturen
                dringende[j] += zending;
            }
            levvac[j] += zending; // dit (levvac[j]) is finaal hoeveel we van dit vaccin naar dit centrum sturen

            vaccins[i]->setVoorraad(vaccins[i]->getVoorraad() - levvac[j]);
            tot_vacs[i] += levvac[j];
            if (levvac[j] > 0) {
                tot_lading[i] ++;
            }
            tot_lading[i] += levvac[j]/vaccins[i]->getLevering();
            tot_vacs[i] += levvac[j];

            (*centra[j])->vaccins[i]->setVoorraad((*centra[j])->vaccins[i]->getVoorraad() + levvac[j]); // dit is de echte levering van getallen (vaccins) aan het centrum
        }
    }
    //alles van/voor leveringen is gedaan
    // we gaan het nog efkes uitprinten
    for (unsigned int j = 0; j < centra.size(); j++) {
        onStream << "Er werden " << tot_lading[j] << " ladingen ("<< tot_vacs[j] <<" vaccins) getransporteerd naar " << (*centra[j])->getNaam()<< "." <<std::endl;
    }

}


bool Hub::centrumVerbonden(const Centrum* centrum) const{
    REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling centrumVerbonden");
    REQUIRE(centrum->properlyInitialized(), "Centrum wasn't initialized when calling centrumVerbonden");
    bool isVerbonden = false;
    for (unsigned int i = 0; i<centra.size(); i++){
        if(centrum->getNaam() == (*centra[i])->getNaam() and centrum->getAdres() == (*centra[i])->getAdres()){
            isVerbonden = true;
        }
    }
    return isVerbonden;
}
/*
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
            simuleerTransport(onStream,(*centra[i]));
        }

        for (unsigned int i = 0; i < centra.size(); i++) {
            (*centra.at(i))->vaccineren(onStream, dag);
        }
        dag++;
    }
}
*/