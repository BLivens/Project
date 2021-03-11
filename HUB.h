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
    int getVaccins() const;
    int getInterval();
    int getTransport() const;
    int getLevering() const;
    void setLevering(int aantal_vaccins);
    void lowerVaccins(int aantal_vaccins);
    void raiseVaccins(int aantal_vaccins);
    void setVaccins(int aantal_vaccins);
    void setInterval(int aantal_dagen);
    void setTransport(int aantal_vaccins);
    void simulateTransport(std::ostream& onStream, Centrum& centrum);
    int berekenLadingen(const Centrum& centrum) const;
    std::vector<Centrum> centra;

private:
    int levering;
    int vaccins;
    int interval;
    int transport;
};

#endif //PROJECT_HUB_H
