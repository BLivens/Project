#include <vector>
#include <string>
#include <iostream>
#include "DesignByContract.h"


#ifndef PROJECT_VACCIN_H
#define PROJECT_VACCIN_H


class Vaccin {
public:
    /**
    \n ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
    */
    Vaccin();
    bool properlyInitialized() const;
    /**
    \n REQUIRE(this->properlyInitialized(), "Vaccin wasn't initialized when calling getType");
    \n ENSURE((!result.empty(),"getType must return a non-empty string");
    */
    std::string getType() const;
    /**
    \n REQUIRE(this->properlyInitialized(), "Vaccin wasn't initialized when calling setType");
    \n REQUIRE((!nieuw_type.empty()),"Type must be a non-empty string");
    \n ENSURE((getType() == nieuw_type), "setType postcondition failure");
    */
    void setType(std::string nieuw_type);
    /**
    \n REQUIRE(this->properlyInitialized(),"Vaccin wasn't initialized when calling getInterval");
    \n ENSURE((result>0),"getInterval must return a strictly positive integer");
    */
    int getInterval() const;
    /**
    \n REQUIRE(this->properlyInitialized(),"Vaccin wasn't initialized when calling setInterval");
    \n REQUIRE((aantal_dagen>0),"aantal_dagen must be a strictly positive integer");
    \n ENSURE((getInterval() == aantal_dagen), "setInterval postcondition failure");
    */
    void setInterval(int aantal_dagen);
    /**
    \n REQUIRE(this->properlyInitialized(),"Vaccin wasn't initialized when calling getTransport");
    \n ENSURE((result>0),"getTransport must return a strictly positive integer");
    */
    int getTransport() const;
    /**
    \n REQUIRE(this->properlyInitialized(), "Vaccin wasn't initialized when calling setTransport");
    \n REQUIRE((aantal_vaccins>0), "aantal_vaccins must be a strictly positive integer");
    \n ENSURE((getTransport() == aantal_vaccins), "setTransport postcondition failure");
    */
    void setTransport(int aantal_vaccins);
    /**
    \n REQUIRE(this->properlyInitialized(), "Vaccin wasn't initialized when calling getLevering");
    \n ENSURE((result>=0),"getLevering must return a positive integer");
    */
    int getLevering() const;
    /**
    \n REQUIRE(this->properlyInitialized(),"Vaccin wasn't initialized when calling setLevering");
    \n REQUIRE((aantal_vaccins>=0), "aantal_vaccins must be a positive integer");
    \n ENSURE((getLevering() == aantal_vaccins), "setLevering postcondition failure");
    */
    void setLevering(int aantal_vaccins);
    /**
    \n REQUIRE(this->properlyInitialized(), "Vaccin wasn't initialized when calling getTemperatuur");
    */
    int getTemperatuur() const;
    /**
    \n REQUIRE(this->properlyInitialized(),"Vaccin wasn't initialized when calling setTemperatuur");
    \n ENSURE((getTemperatuur() == nieuwe_temperatuur), "setTemperatuur postcondition failure");
    */
    void setTemperatuur(int nieuwe_temperatuur);
    /**
    \n REQUIRE(this->properlyInitialized(), "Vaccin wasn't initialized when calling getHernieuwing");
    \n ENSURE((result>=0),"getHernieuwing must return a positive integer");
    */
    int getHernieuwing() const;
    /**
    \n REQUIRE(this->properlyInitialized(),"Vaccin wasn't initialized when calling setHernieuwing");
    \n REQUIRE((nieuwe_hernieuwing>=0), "nieuwe_hernieuwing must be a positive integer");
    \n ENSURE((getHernieuwing() == nieuwe_hernieuwing), "setHernieuwing postcondition failure");
    */
    void setHernieuwing(int nieuwe_hernieuwing);
    /**
    \n REQUIRE(this->properlyInitialized(), "Vaccin wasn't initialized when calling getVoorraad");
    \n ENSURE((result>=0),"getVoorraad must return a positive integer");
    */
    int getVoorraad() const;
    /**
    \n REQUIRE(this->properlyInitialized(),"Vaccin wasn't initialized when calling setVoorraad");
    \n REQUIRE((aantal_vaccins>=0), "aantal_vaccins must be a positive integer");
    \n ENSURE((setVoorraad() == aantal_vaccins), "setVoorraad postcondition failure");
    */
    void setVoorraad(int aantal_vaccins);


private:
    Vaccin* _initCheck;
    std::string type;
    int voorraad;
    int hernieuwing;
    int temperatuur;
    int levering;
    int interval;
    int transport;
};

#endif //PROJECT_VACCIN_H

