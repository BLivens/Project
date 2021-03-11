#include "HUB.h"

Hub::Hub(){
}

int Hub::getVaccins() const{
    return vaccins;
}

int Hub::getInterval() const{
    return interval;
}
int Hub::getTransport() const{
    return transport;
}
void Hub::lowerVaccins(int aantal_vaccins) {
    vaccins = getVaccins() - aantal_vaccins;
}
int Hub::getLevering() const{
    return levering;
}

void Hub::raiseVaccins(int aantal_vaccins) {
    vaccins = getVaccins() + aantal_vaccins;
}


void Hub::setVaccins(int aantal_vaccins) {
    vaccins = aantal_vaccins;
}

void Hub::setInterval(int aantal_dagen) {
    interval = aantal_dagen;
}

void Hub::setTransport(int aantal_vaccins) {
    transport = aantal_vaccins;
}

void Hub::setLevering(int aantal_vaccins) {
    levering = aantal_vaccins;
}

void Hub::simulateTransport(std::ostream &onStream, Centrum& centrum) {
    // bereken aantal ladingen
    int aantal_ladingen = berekenLadingen(centrum);
    // bereken aantal vaccins
    int aantal_vaccins = aantal_ladingen * getTransport();
    // verlaag het aantal vaccins in de Hub met de correcte hoeveelheid
    lowerVaccins(aantal_vaccins);
    // verhoog het aantal vaccins in het centrum met de correcte hoeveelheid
    centrum.vaccins = centrum.vaccins + aantal_vaccins;
    // schrijf overzicht uit
    onStream << "Er werden " << aantal_ladingen << " ladingen ("<< aantal_vaccins <<" vaccins) getransporteerd naar " << centrum.naam<< "." <<std::endl;
}

int Hub::berekenLadingen(const Centrum &centrum) const {
    // declareer ladingen
    int ladingen;
    // indien er meer vaccins in het centrum aanwezig zijn dan de capaciteit van het centrum worden er geen ladingen geleverd
    if (centrum.capaciteit < centrum.vaccins){
        ladingen = 0;
    }
    // indien er wel ladingen nodig zijn
    else{
        // bereken benodigde ladingen
        int nodige_ladingen = (centrum.capaciteit - centrum.vaccins)/getTransport();
        if ((centrum.capaciteit - centrum.vaccins)%getTransport() != 0){
            nodige_ladingen = nodige_ladingen + 1;
        }
        // bereken het maximaal aantal ladingen dat het centrum kan ontvangen
        int max_ladingen = (centrum.capaciteit*2 - centrum.vaccins)/getTransport();
        // bereken het aantal beschikbare ladingen in de Hub
        int beschikbare_ladingen = getVaccins()/getTransport();
        // Indien er minder ladingen beschikbaar zijn dan geleverd moeten worden
        if (beschikbare_ladingen<nodige_ladingen){
            // lever alle ladingen die in de Hub aanwezig zijn
            ladingen = beschikbare_ladingen;
        }
        // anders als de ladingen zo groot zijn dat het max aantal ladingen overschreden worden
        else if (nodige_ladingen>max_ladingen){
            // er wordt niets geleverd
            ladingen = 0;
        }
        // anders is het aantal ladingen gelijk aan de benodigde ladingen
        else {
            ladingen = nodige_ladingen;
        }
    }
    return ladingen;
}





