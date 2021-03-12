#include "Centrum.h"

void Centrum::vaccineren() {
    int ongevaccineerden = inwoners - gevacineerden;
    int teVaccineren = std::min(vaccins, capaciteit);
    teVaccineren = std::min(ongevaccineerden, teVaccineren);

    vaccins = vaccins - teVaccineren;
    gevacineerden = gevacineerden + teVaccineren;
    if (teVaccineren != 0) { // enkel printen als we minstens een mens vaccineren
        std::cout << "Er werden " << teVaccineren << " inwoners gevaccineerd in " << naam << ".\n";
    }
}
