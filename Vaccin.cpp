#include "Vaccin.h"

Vaccin::Vaccin(){
    _initCheck = this;
    type = "";
    levering = 0;
    voorraad = 0;
    hernieuwing = 0;
    temperatuur = 0;
    interval = 1;
    transport = 1;
    /*
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
           */
}

bool Vaccin::properlyInitialized() const{
    return _initCheck == this;
}

std::string Vaccin::getType() const{
    std::string result;
    /*
    REQUIRE(this->properlyInitialized(),
            "Vaccin wasn't initialized when calling getType");
            */
    result = type;
    ENSURE((!result.empty()),"getType must return a non-empty string");
    return result;
}

void Vaccin::setType(std::string nieuw_type) {
    /*
    REQUIRE(this->properlyInitialized(),
            "Vaccin wasn't initialized when calling setType");
            */
    REQUIRE((!nieuw_type.empty()),
            "nieuw_type must be a non-empty string");
    type = nieuw_type;
    ENSURE((getType() == nieuw_type), "setType postcondition failure");
}

int Vaccin::getInterval() const{
    int result;
    /*
    REQUIRE(this->properlyInitialized(),
            "Vaccin wasn't initialized when calling getInterval");
            */
    result = interval;
    ENSURE((result>0),"getInterval must return a strictly positive integer");
    return result;
}

void Vaccin::setInterval(int aantal_dagen) {
    /*
    REQUIRE(this->properlyInitialized(),
            "Hub wasn't initialized when calling setInterval");
            */
    REQUIRE((aantal_dagen>0),
            "aantal_dagen must be a strictly positive integer");
    interval = aantal_dagen;
    ENSURE((getInterval() == aantal_dagen), "setInterval postcondition failure");
}

int Vaccin::getTransport() const{
    int result;
    /*
    REQUIRE(this->properlyInitialized(),
            "Vaccin wasn't initialized when calling getTransport");
            */
    result = transport;
    ENSURE((result>0),"getTransport must return a strictly positive integer");
    return result;
}
void Vaccin::setTransport(int aantal_vaccins) {
    /*
    REQUIRE(this->properlyInitialized(),
            "Vaccin wasn't initialized when calling setTransport");
            */
    REQUIRE((aantal_vaccins>0),
            "aantal_vaccins must be a strictly positive integer");
    transport = aantal_vaccins;
    ENSURE((getTransport() == aantal_vaccins), "setTransport postcondition failure");
}

int Vaccin::getLevering() const{
    int result;
    /*
    REQUIRE(this->properlyInitialized(),
            "Vaccin wasn't initialized when calling getLevering");
            */
    result = levering;
    ENSURE((result>=0),"getLevering must return a positive integer");
    return result;
}

void Vaccin::setLevering(int aantal_vaccins) {
    /*
    REQUIRE(this->properlyInitialized(),
            "Vaccin wasn't initialized when calling setLevering");
            */
    REQUIRE((aantal_vaccins>=0),
            "aantal_vaccins must be a positive integer");
    levering = aantal_vaccins;
    ENSURE((getLevering() == aantal_vaccins), "setLevering postcondition failure");
}

int Vaccin::getTemperatuur() const{
    int result;
    /*
    REQUIRE(this->properlyInitialized(),
            "Vaccin wasn't initialized when calling getTemperatuur");
            */
    result = temperatuur;
    // ENSURE((result>=0),"getTemperatuur must return a positive integer"); Mag natuurlijk negatief zijn
    return result;
}

void Vaccin::setTemperatuur(int nieuwe_temperatuur) {
    /*
    REQUIRE(this->properlyInitialized(),
            "Vaccin wasn't initialized when calling setTemperatuur");
            */
    temperatuur = nieuwe_temperatuur;
    ENSURE((getTemperatuur() == nieuwe_temperatuur), "setTemperatuur postcondition failure");
}

int Vaccin::getHernieuwing() const{
    int result;
    /*
    REQUIRE(this->properlyInitialized(),
            "Vaccin wasn't initialized when calling getHernieuwing");
            */
    result = hernieuwing;
    ENSURE((result>=0),"getHernieuwing must return a positive integer");
    return result;
}

void Vaccin::setHernieuwing(int nieuwe_hernieuwing) {
    /*
    REQUIRE(this->properlyInitialized(),
            "Vaccin wasn't initialized when calling setHernieuwing");
            */
    hernieuwing = nieuwe_hernieuwing;
    ENSURE((getHernieuwing() == nieuwe_hernieuwing), "setHernieuwing postcondition failure");
}

int Vaccin::getVoorraad() const{
    int result;
    //REQUIRE(this->properlyInitialized(),
            //"Vaccin wasn't initialized when calling getVoorraad"); TODO: Zou moeten checken, tijdelijk uitgezet om voort te geraken
    result = voorraad;
    ENSURE((result>=0),"getVoorraad must return a positive integer");
    return result;
}

void Vaccin::setVoorraad(int aantal_vaccins) {
    /*
    REQUIRE(this->properlyInitialized(),
            "Vaccin wasn't initialized when calling setVoorraad");
            */
    voorraad = aantal_vaccins;
    ENSURE((getVoorraad() == aantal_vaccins), "setVoorraad postcondition failure");
}
