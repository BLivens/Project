#include <vector>
#include <string>
#include <iostream>
#include "Centrum.h"
#include "DesignByContract.h"


#ifndef PROJECT_HUB_H
#define PROJECT_HUB_H

class Hub {
public:
    Hub();
    bool properlyInitialized() const;
    int getVaccins() const;
    void setVaccins(int aantal_vaccins);
    int getInterval() const;
    void setInterval(int aantal_dagen);
    int getTransport() const;
    void setTransport(int aantal_vaccins);
    int getLevering() const;
    void setLevering(int aantal_vaccins);
    void verlaagVaccins(int aantal_vaccins);
    void verhoogVaccins(int aantal_vaccins);
    int berekenLadingen(const Centrum& centrum) const;
    void simuleerTransport(std::ostream& onStream, Centrum& centrum);
    std::vector<Centrum> centra;

private:
    Hub* _initCheck;
    int levering;
    int vaccins;
    int interval;
    int transport;
};

#endif //PROJECT_HUB_H
