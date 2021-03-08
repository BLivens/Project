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
    int getVaccins();
    int getInterval();
    int getTransport();
    int getLevering();
    void setLevering(int aantal_vaccins);
    void lowerVaccins(int aantal_vaccins);
    void raiseVaccins(int aantal_vaccins);
    void setVaccins(int aantal_vaccins);
    void setInterval(int aantal_dagen);
    void setTransport(int aantal_vaccins);
    void simulateTransport(std::ostream& onStream);
    std::vector<Centrum> centra;

private:
    int levering;
    int vaccins;
    int interval;
    int transport;
};

#endif //PROJECT_HUB_H
