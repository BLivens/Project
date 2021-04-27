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
    \n REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling getVaccins");
    */
    //std::vector<Vaccin> getVaccins() const;
    /**
    \n REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling setVaccins");
    \n ENSURE((getVaccins() == nieuwe_vaccins), "setVaccins postcondition failure");
    */
    //void setVaccins(std::vector<Vaccin> vaccins);
    /**
    \n REQUIRE(this->properlyInitialized(),"Hub wasn't initialized when calling getInterval");
    \n ENSURE((result>0),"getInterval must return a strictly positive integer");
    */
    //int getInterval() const;
    /**
    \n REQUIRE(this->properlyInitialized(),"Hub wasn't initialized when calling setInterval");
    \n REQUIRE((aantal_dagen>0),"aantal_dagen must be a strictly positive integer");
    \n ENSURE((getInterval() == aantal_dagen), "setInterval postcondition failure");
    */
    //void setInterval(int aantal_dagen);
    /**
   \n REQUIRE(this->properlyInitialized(),"Hub wasn't initialized when calling getVoorraad");
   \n ENSURE((result>0),"getVoorraad must return a strictly positive integer");
   */
    int getVoorraad() const;
    /**
    \n REQUIRE(this->properlyInitialized(),"Hub wasn't initialized when calling setVoorraad");
    \n REQUIRE((voorraad>0),"voorraad must be a strictly positive integer");
    \n ENSURE((getVoorraad() == aantal_vaccins), "setVoorraad postcondition failure");
    */
    //void setVoorraad(int aantal_vaccins);
    /**
    \n REQUIRE(this->properlyInitialized(),"Hub wasn't initialized when calling getTransport");
    \n ENSURE((result>0),"getTransport must return a strictly positive integer");
    */
    //int getTransport() const;
    /**
    \n REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling setTransport");
    \n REQUIRE((aantal_vaccins>0), "aantal_vaccins must be a strictly positive integer");
    \n ENSURE((getTransport() == aantal_vaccins), "setTransport postcondition failure");
    */
    //void setTransport(int aantal_vaccins);
    /**
    \n REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling getLevering");
    \n ENSURE((result>=0),"getLevering must return a positive integer");
    */
    //int getLevering() const;
    /**
    \n REQUIRE(this->properlyInitialized(),"Hub wasn't initialized when calling setLevering");
    \n REQUIRE((aantal_vaccins>=0), "aantal_vaccins must be a positive integer");
    \n ENSURE((getLevering() == voorraad), "setLevering postcondition failure");
    */
    //void setLevering(int aantal_vaccins);
    /**
    \n REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling berekenLadingen");
    \n REQUIRE(centrum->properlyInitialized(), "Centrum wasn't initialized when calling berekenLadingen");
    \n REQUIRE(centrumVerbonden(centrum), "berekenLadingen requires centrum to be linked with Hub.");
    \n ENSURE(result >= 0, "berekenLadingen must return a positive integer");
    */
    //int berekenLadingen(const Centrum* centrum) const;
    /**;
    \n REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling berekenLadingen");
    \n REQUIRE(centrum->properlyInitialized(), "Centrum wasn't initialized when calling simuleerTransport");
    \n REQUIRE(centrumVerbonden(centrum), "simuleerTransport requires centrum to be linked with Hub.");
    */
    void simuleerTransport(std::ostream& onStream, Centrum* centrum);
    /**
    \n REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling simuleren");
    \n REQUIRE(dagen>=0, "Dagen must be an integer greater or equal to 0.");
    */
    void simuleren(int dagen, std::ostream &onStream);
    /**
    \n REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling centrumVerbonden);
    \n REQUIRE(centrum->properlyInitialized(), "Centrum wasn't initialized when calling centrumVerbonden");
    */
    bool centrumVerbonden(const Centrum* centrum) const;
    std::vector<Centrum*> centra;
    std::vector<Vaccin*> vaccins;
private:
    Hub* _initCheck;
};

#endif //PROJECT_HUB_H
