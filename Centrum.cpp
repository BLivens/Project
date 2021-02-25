#include "Centrum.h"

void Centrum::vaccineren() {
    int ongevaccineerden = inwoners - gevacineerden;
    int teVaccineren = std::min(vaccins, capaciteit);
    teVaccineren = std::min(ongevaccineerden, teVaccineren);

    vaccins = vaccins - teVaccineren;
    gevacineerden = gevacineerden + teVaccineren;
    std::cout << "Er werden " << teVaccineren << " inwoners gevaccineerd in " << naam << ".\n";
    // mogelijks enkel printen als er niet 0 mensen gevaccineerd worden, we zullen wel zien.
}

