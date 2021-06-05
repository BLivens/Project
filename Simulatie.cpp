//
// Created by michel on 01.06.21.
//

#include "Simulatie.h"

Simulatie::Simulatie() {
    _initCheck = this;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
}

bool Simulatie::properlyInitialized() const{
    return _initCheck == this;

}

void Simulatie::simuleren(int dagen, std::ostream &onStream) {
    REQUIRE(this->properlyInitialized(), "Simulatie wasn't initialized when calling simuleren");
    REQUIRE(dagen>=0, "Dagen must be an integer greater or equal to 0.");
    int dag = 0;
    while (dag < dagen) {
        for (unsigned int j = 0; j < hubs.size(); j++){
            for (unsigned int i = 0; i < hubs[j]->vaccins.size(); i++) {
                if (dag % hubs[j]->vaccins[i]->getInterval() == 0) {
                    int plus = hubs[j]->vaccins[i]->getLevering();
                    hubs[j]->vaccins[i]->setVoorraad(hubs[j]->vaccins[i]->getVoorraad() + plus);
                    // bijhouden van aantal geleverde vacc per type
                    std::string vacc_naam = hubs[j]->vaccins[i]->getType();
                    if (geleverde_vacc.find(vacc_naam) == geleverde_vacc.end()){
                        geleverde_vacc[vacc_naam] = plus;
                    }
                    else{
                        geleverde_vacc[vacc_naam] = geleverde_vacc[vacc_naam] + plus;
                    }
                }
            }
            hubs[j]->simuleerTransport(onStream, dag);
        }

        for (unsigned int i = 0; i < centra.size(); i++) {
            centra.at(i)->vaccineren(onStream, dag);
        }
        dag++;
    }
}