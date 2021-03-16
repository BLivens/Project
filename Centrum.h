#include <string>
#include <iostream>
#include "DesignByContract.h"

#ifndef PROJECT_CENTRUM_H
#define PROJECT_CENTRUM_H

class Centrum {
public:
    Centrum();
    bool properlyInitialized() const;
    void vaccineren(std::ostream &onStream);

    std::string getNaam() const;
    void setNaam(std::string nieuwe_naam);
    std::string getAdres() const;
    void setAdres(std::string nieuw_adres);
    int getInwoners() const;
    void setInwoners(int aantal_inwoners);
    int getCapaciteit() const;
    void setCapaciteit(int aantal_capaciteit);
    int getVaccins() const;
    void setVaccins(int aantal_capaciteit);
    int getGevacineerden() const;
    void setGevacineerden(int aantal_gevacineerden);

private:
    Centrum* _initCheck;
    std::string naam;
    std::string adres;
    int inwoners;
    int capaciteit;
    int vaccins;
    int gevacineerden;


};

#endif //PROJECT_CENTRUM_H
