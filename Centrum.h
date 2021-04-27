#include <string>
#include <vector>
#include "Vaccin.h"
#include <iostream>
#include <map>
#include "DesignByContract.h"

#ifndef PROJECT_CENTRUM_H
#define PROJECT_CENTRUM_H

class Centrum {
public:
    /**
    \n ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
    */
    Centrum();
    bool properlyInitialized() const;
    /**
    \n REQUIRE(this->properlyInitialized(), "Centrum wasn't initialized when calling vaccineren");
    \n  REQUIRE((dag>=0), "dag must be a positive integer");
    */
    void vaccineren(std::ostream &onStream, int dag);
    /**
    \n REQUIRE(this->properlyInitialized(), "Centrum wasn't initialized when calling getNaam");
    \n ENSURE((!result.empty()),"getNaam can't return empty string");
    */
    std::string getNaam() const;
    /**
    \n REQUIRE(this->properlyInitialized(), "Centrum wasn't initialized when calling setNaam");
    \n REQUIRE((!nieuwe_naam.empty()), "naam can't be empty");
    \n ENSURE((getNaam() == nieuwe_naam), "setNaam postcondition failure");
     */
    void setNaam(std::string nieuwe_naam);
    /**
    \n REQUIRE(this->properlyInitialized(), "Hub wasn't initialized when calling getAdres");
    \n ENSURE((!result.empty()),"getAdres can't return empty string");
    */
    std::string getAdres() const;
    /**
    \n REQUIRE(this->properlyInitialized(), "Centrum wasn't initialized when calling setAdres");
    \n REQUIRE((!nieuw_adres.empty()),"adres can't be empty");
    \n ENSURE((getAdres() == nieuw_adres),"setAdres postconditiion failure");
    */
    void setAdres(std::string nieuw_adres);
    /**
    \n REQUIRE(this->properlyInitialized(), "Centrum wasn't initialized when calling getInwoners");
    \n ENSURE((result>=0),"getInwoners must return a positive integer");
    */
    int getInwoners() const;
    /**
    \n REQUIRE(this->properlyInitialized(), "Centrum wasn't initialized when calling setInwoners");
    \n REQUIRE((aantal_inwoners>=0),"aantal_inwoners must be a positive integer");
    \n ENSURE((getInwoners() == aantal_inwoners), "setInwoners postcondition failure");
    */
    void setInwoners(int aantal_inwoners);
    /**
    \n REQUIRE(this->properlyInitialized(), "Centrum wasn't initialized when calling getCapaciteit");
    \n ENSURE((result>=0),"getCapaciteit must return a positive integer");
    */
    int getCapaciteit() const;
    /**
    \n REQUIRE(this->properlyInitialized(), "Centrum wasn't initialized when calling setCapaciteit");
    \n REQUIRE((aantal_capaciteit>=0), "aantal_capaciteit must be a positive integer");
    \n ENSURE((getCapaciteit() == aantal_capaciteit), "setCapaciteit postcondition failure");
    */
    void setCapaciteit(int aantal_capaciteit);
    /**
    \n REQUIRE(this->properlyInitialized(), "Centrum wasn't initialized when calling getVoorraad");
    \n ENSURE((result>=0) && (result<= getCapaciteit()*2),"getVoorraad must return a positive integer lower or equal to capaciteit*2");
    */
    int getVoorraad() const;
    /**
    \n REQUIRE(this->properlyInitialized(), "Centrum wasn't initialized when calling getGevacineerden");
    \n ENSURE((result>=0),"getGevacineerden must return a positive integer");
    */
    int getGevacineerden() const;
    /**
    \n REQUIRE(this->properlyInitialized(), "Centrum wasn't initialized when calling setGevacineerden");
    \n REQUIRE((aantal_gevacineerden>=0), "aantal_gevacineerden must be a positive integer");;
    \n ENSURE((getGevacineerden() == aantal_gevacineerden), "setGevacineerden postcondition failure");
    */
    void setGevacineerden(int aantal_gevacineerden);


    std::map<std::pair<int, std::string>, int> log;
    std::vector<Vaccin*> vaccins;
private:
    Centrum* _initCheck;
    std::string naam;
    std::string adres;
    int inwoners;
    int capaciteit;
    int gevacineerden;
};

#endif //PROJECT_CENTRUM_H
