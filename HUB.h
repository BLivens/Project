#include <vector>
#include <string>
#include <iostream>
#include "Centrum.h"
#include "Vaccin.h"
#include "DesignByContract.h"


#ifndef PROJECT_HUB_H
#define PROJECT_HUB_H

class Hub {
public:
    /**
    \n ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
    */
    Hub();
    bool properlyInitialized() const;
    /**
    \n REQUIRE(this->properlyInitialized(),"Hub wasn't initialized when calling getVoorraad");
    \n ENSURE((result>=0),"getVoorraad must return a positive integer");
    */
    int getVoorraad() const;
    /**;
    \n REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling simuleerTransport");
    \n REQUIRE(centrum->properlyInitialized(), "Centrum wasn't initialized when calling simuleerTransport");
    \n REQUIRE(centrumVerbonden(centrum), "simuleerTransport requires centrum to be linked with Hub.");
    */
    void simuleerTransport(std::ostream& onStream, int dag);
    /**
    \n REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling centrumVerbonden);
    \n REQUIRE(centrum->properlyInitialized(), "Centrum wasn't initialized when calling centrumVerbonden");
    */
    bool centrumVerbonden(const Centrum* centrum) const;
    std::vector<Centrum**> centra;
    std::vector<Vaccin*> vaccins;
private:
    Hub* _initCheck;
};

#endif //PROJECT_HUB_H
