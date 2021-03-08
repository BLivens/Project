#include "HUB.h"

Hub::Hub(){
}

int Hub::getVaccins() {
    return vaccins;
}

int Hub::getInterval() {
    return interval;
}
int Hub::getTransport(){
    return transport;
}
void Hub::lowerVaccins(int aantal_vaccins) {
    vaccins = getVaccins() - aantal_vaccins;
}
int Hub::getLevering() {
    return levering;
}

void Hub::raiseVaccins(int aantal_vaccins) {
    vaccins = getVaccins() + aantal_vaccins;
}

void Hub::simulateTransport(std::ostream& onStream) {
    // Bereken aantal ladingen
    int aantal_beschikbare_ladingen = getVaccins()/getTransport();
    int totaal_aantal_verzonden_ladingen = 0;

    for (unsigned int i = 0; i<centra.size() ; i++){
        int nodige_ladingen = (centra[i].capaciteit - centra[i].vaccins)/getTransport()+1;
        int max_aantal_ladingen = (centra[i].capaciteit*2 - centra[i].vaccins)/getTransport();
        int verzonden_ladingen = 0;
        while (aantal_beschikbare_ladingen > 0 and nodige_ladingen>0 and verzonden_ladingen<max_aantal_ladingen){
            verzonden_ladingen = verzonden_ladingen + 1;
            nodige_ladingen = nodige_ladingen - 1;
            aantal_beschikbare_ladingen = aantal_beschikbare_ladingen - 1;

        }
        totaal_aantal_verzonden_ladingen = totaal_aantal_verzonden_ladingen +verzonden_ladingen;
        int verzonden_vaccins = verzonden_ladingen * transport;
        centra[i].vaccins = centra[i].vaccins + verzonden_vaccins;
        onStream << "Er werden " << verzonden_ladingen << " ladingen ("<< verzonden_vaccins <<" vaccins) getransporteerd naar " << centra[i].naam<< "." <<std::endl;
    }

    // Verlaag het aantal vaccins in de HUB
    int totaal_aantal_verzonden_vaccins = totaal_aantal_verzonden_ladingen *getTransport();
    std::cout << getTransport() << " " << totaal_aantal_verzonden_ladingen <<std::endl;
    lowerVaccins(totaal_aantal_verzonden_vaccins);

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






