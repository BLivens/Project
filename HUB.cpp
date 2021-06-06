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

        for (unsigned int j = 0; j < centra.size(); j++) { // de loop van de eerste kans
            tweedeDosis = (*centra[j])->getTweedes(dag, type) - (*centra[j])->vaccins[i]->getVoorraad(); // dit is hoeveel het centrum tekort komt, hopelijk kunnen we het sturen

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
        double wachttijd;

        if (dag == 0) {
            wachttijd = vaccins[i]->getInterval();
        } else {
            wachttijd = vaccins[i]->getInterval() % dag;
        }

        double doel = (vaccins[i]->getVoorraad()/wachttijd)/centra.size();

        for (unsigned int j = 0; j < centra.size(); j++) { // de loop van de tweede kans
            double zending = std::min((double)((*centra[j])->getCapaciteit()*2 - (*centra[j])->getVoorraad()), doel); // het minumum van wat we willen sturen en wat we kunnen sturen
            if (vaccins[i]->getTemperatuur() < 0) {
                zending = std::min(zending, (double)((*centra[j])->getCapaciteit() - dringende[j])); // als het dezelfde dag nog geprikt moet worden kunnen we misschien maar minder sturen
                dringende[j] += zending;
            }
            levvac[j] += zending;
            // afronden op ladingen
            /*
            int overschot = levvac[j] % vaccins[i]->getLevering();
            levvac[j] -= overschot;  // FINAAL: dit is echt hoeveel we van dit vaccin naar dit centrum leveren
             */
            vaccins[i]->setVoorraad(vaccins[i]->getVoorraad() - levvac[j]);
            tot_vacs[i] += levvac[j];
            tot_lading[i] += 1+ levvac[j]/vaccins[i]->getLevering();
            // dringende ook aanpassen
            (*centra[j])->vaccins[i]->setVoorraad((*centra[j])->vaccins[i]->getVoorraad() + levvac[j]); // dit is de echte levering van getallen (vaccins) aan het centrum
        }
    }
    //alles van/voor leveringen is gedaan
    // we gaan het nog efkes uitprinten
    for (unsigned int j = 0; j < centra.size(); j++) {
        onStream << "Er werden " << tot_lading[j] << " ladingen ("<< tot_vacs[j] <<" vaccins) getransporteerd naar " << (*centra[j])->getNaam()<< "." <<std::endl;
    }
/*
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
        for (unsigned j = 0; j < centrum->vaccins.size(); j++){
            if (vaccins[i]->getType() == centrum->vaccins[j]->getType()){
                centrum->vaccins[j]->setVoorraad(centrum->vaccins[j]->getVoorraad()+result*vaccins[i]->getTransport());
            }
        }
        aantal_ladingen = aantal_ladingen + result;
        aantal_vaccins = aantal_vaccins + result * vaccins[i]->getTransport();
    }
    onStream << "Er werden " << aantal_ladingen << " ladingen ("<< aantal_vaccins <<" vaccins) getransporteerd naar " << centrum->getNaam()<< "." <<std::endl;

*/
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