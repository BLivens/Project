#include "Centrum.h"

Centrum::Centrum() {
    _initCheck = this;
    naam = "a";
    adres = "a";
    inwoners = 0;
    capaciteit = 0;
    voorraad = 0;
    gevacineerden = 0;
    ENSURE(properlyInitialized(),
           "constructor must end in properlyInitialized state");
}

bool Centrum::properlyInitialized() const{
    return _initCheck == this;
}

std::string Centrum::getNaam() const{
    std::string result;
    REQUIRE(this->properlyInitialized(),
            "Centrum wasn't initialized when calling getNaam");
    result = naam;
    ENSURE((!result.empty()),"getNaam can't return empty string");
    return result;
}

void Centrum::setNaam(std::string nieuwe_naam) {
    REQUIRE(this->properlyInitialized(),
            "Centrum wasn't initialized when calling setNaam");
    REQUIRE((!nieuwe_naam.empty()),
            "naam can't be empty");
    naam = nieuwe_naam;
    ENSURE((getNaam() == nieuwe_naam), "setNaam postcondition failure");
}

std::string Centrum::getAdres() const{
    std::string result;
    REQUIRE(this->properlyInitialized(),
            "Hub wasn't initialized when calling getAdres");
    result = adres;
    ENSURE((!result.empty()),"getAdres can't return empty string");
    return result;
}

void Centrum::setAdres(std::string nieuw_adres) {
    REQUIRE(this->properlyInitialized(),
            "Centrum wasn't initialized when calling setAdres");
    REQUIRE((!nieuw_adres.empty()),
            "adres can't be empty");
    adres = nieuw_adres;
    ENSURE((getAdres() == nieuw_adres), "setAdres postcondition failure");
}

int Centrum::getInwoners() const{
    int result;
    REQUIRE(this->properlyInitialized(),
            "Centrum wasn't initialized when calling getInwoners");
    result = inwoners;
    ENSURE((result>=0),"getInwoners must return a positive integer");
    return result;
}

void Centrum::setInwoners(int aantal_inwoners) {
    REQUIRE(this->properlyInitialized(),
            "Centrum wasn't initialized when calling setInwoners");
    REQUIRE((aantal_inwoners>=0),
            "aantal_inwoners must be a positive integer");
    inwoners = aantal_inwoners;
    ENSURE((getInwoners() == aantal_inwoners), "setInwoners postcondition failure");
}


int Centrum::getCapaciteit() const{
    int result;
    REQUIRE(this->properlyInitialized(),
            "Centrum wasn't initialized when calling getCapaciteit");
    result = capaciteit;
    ENSURE((result>=0),"getCapaciteit must return a positive integer");
    return result;
}

void Centrum::setCapaciteit(int aantal_capaciteit) {
    REQUIRE(this->properlyInitialized(),
            "Centrum wasn't initialized when calling setCapaciteit");
    REQUIRE((aantal_capaciteit>=0),
            "aantal_capaciteit must be a positive integer");
    capaciteit = aantal_capaciteit;
    ENSURE((getCapaciteit() == aantal_capaciteit), "setCapaciteit postcondition failure");
}

int Centrum::getVoorraad() const {
    int result = 0;
    REQUIRE(this->properlyInitialized(),
            "Centrum wasn't initialized when calling getVoorraad");
    for (unsigned int i =0; i < vaccins.size(); i++) {
        result+= vaccins[i].getVoorraad();
    }
    ENSURE((result>=0) && (result<= getCapaciteit()*2),"getVoorraad must return a positive integer lower or equal to capaciteit*2");
    return result;
}

void Centrum::setVoorraad(int aantal_vaccins) {
    REQUIRE(this->properlyInitialized(),
            "Centrum wasn't initialized when calling setVoorraad");
    REQUIRE((aantal_vaccins>=0 && aantal_vaccins <= getCapaciteit()*2),
            "aantal_vaccins must be a positive integer lower or equal to capaciteit*2");
    voorraad = aantal_vaccins;
    // ENSURE((getVoorraad() == aantal_vaccins), "setVoorraad postcondition failure"); Werkt tijdelijk niet,
    //  TODO: getvoorraad gaat halen bij de vaccins zelf, moet bij voorraad zijn en deze functie (setvoorraad) moet veranderen naar een functie die vaccins weghaalt uit de specifieke voorraaden vna vaccins
}

int Centrum::getGevacineerden() const{
    int result;
    REQUIRE(this->properlyInitialized(),
            "Centrum wasn't initialized when calling getGevacineerden");
    result = gevacineerden;
    ENSURE((result>=0),"getGevacineerden must return a positive integer");
    return result;
}

void Centrum::setGevacineerden(int aantal_gevacineerden) {
    REQUIRE(this->properlyInitialized(),
            "Centrum wasn't initialized when calling setGevacineerden");
    REQUIRE((aantal_gevacineerden>=0),
            "aantal_gevacineerden must be a positive integer");
    gevacineerden = aantal_gevacineerden;
    ENSURE((getGevacineerden() == aantal_gevacineerden), "setGevacineerden postcondition failure");
}


std::vector<Vaccin> Centrum::getVaccins() const{
    std::vector<Vaccin> result;
    REQUIRE(this->properlyInitialized(),
           "Hub wasn't initialized when calling getVaccins");
    result = vaccins;
    return result;
}

void Centrum::setVaccins(std::vector<Vaccin*> nieuwe_vaccins) {
    REQUIRE(this->properlyInitialized(),
            "Hub wasn't initialized when calling setVaccins");
    for (unsigned int i = 0; i < nieuwe_vaccins.size(); i++) {
        vaccins.push_back(*nieuwe_vaccins[i]);
    }
    // ENSURE((getVaccins() == nieuwe_vaccins), "setVaccins postcondition failure"); TODO: Dit toch testen
}

/* Voor later misschien
int Centrum::tweedePrik(int dag, std::string type) {
    REQUIRE(this->properlyInitialized(), "Centrum wasn't initialized when calling tweedePrik");
    // TDO : Require dat het een bestaande naam van een vaccin is?
    log[std::make_pair(dag, type)] = 0; // we maken de hoeveelheid van vandaag voorlopig nul, dit wordt in

    Vaccin tempvac = vaccins[0];
    int i = 1;
    while (tempvac.getType() != type) {
        tempvac = vaccins[i];
        i++;
    }

    return 1;
}
*/

void Centrum::vaccineren(std::ostream &onStream, int dag) {
    REQUIRE(this->properlyInitialized(), "Centrum wasn't initialized when calling vaccineren");
    int ongevaccineerden = getInwoners() - getGevacineerden();
    int teVaccineren = std::min(getVoorraad(), getCapaciteit());
    teVaccineren = std::min(ongevaccineerden, teVaccineren);
    int aantal_mensen_gevaccineerd = 0;

    // prioriteit geven aan mensen met al een eerste prikje
    for (unsigned int i = 0; i < vaccins.size(); i++){
        if(vaccins[i].getVoorraad()!=0){
            int dag_eerste_prik = dag-vaccins[i].getHernieuwing();
            std::string type_vacc = vaccins[i].getType();
            std::pair<int,std::string> p = std::make_pair(dag_eerste_prik,type_vacc);
            if (log.count(p)!=0){
                int aantal_vac_type = std::min(teVaccineren, log[p]);
                vaccins[i].setVoorraad(vaccins[i].getVoorraad()-aantal_vac_type);
                log[std::make_pair(dag+1, type_vacc)] += log[std::make_pair(dag, type_vacc)] - aantal_vac_type;
                log[std::make_pair(dag, type_vacc)] = log[std::make_pair(dag, type_vacc)] - aantal_vac_type;
                setGevacineerden(getGevacineerden()+aantal_vac_type);
                teVaccineren = teVaccineren - aantal_vac_type;
                aantal_mensen_gevaccineerd = aantal_mensen_gevaccineerd + aantal_vac_type;
            }
        }
    }
    for (unsigned int j = 0; j < vaccins.size(); j++){
        if(vaccins[j].getVoorraad()!=0 and teVaccineren>0){
            int aantal_vac_type2 = std::min(teVaccineren, vaccins[j].getVoorraad());
            vaccins[j].setVoorraad(vaccins[j].getVoorraad()-aantal_vac_type2);
            if(vaccins[j].getHernieuwing()==0){
                setGevacineerden(getGevacineerden()+aantal_vac_type2);
            }
            else{
                log[std::make_pair(dag,vaccins[j].getType())] = aantal_vac_type2;
            }
            teVaccineren = teVaccineren - aantal_vac_type2;
            aantal_mensen_gevaccineerd = aantal_mensen_gevaccineerd + aantal_vac_type2;
        }
    }
    if (aantal_mensen_gevaccineerd!= 0) { // enkel printen als we minstens een mens vaccineren
        onStream << "Er werden " << aantal_mensen_gevaccineerd << " inwoners gevaccineerd in " << getNaam() << ".\n";
    }
    setVoorraad(getVoorraad()-teVaccineren);
    setGevacineerden(getGevacineerden()+teVaccineren);
    if (teVaccineren != 0) { // enkel printen als we minstens een mens vaccineren
        onStream << "Er werden " << teVaccineren << " inwoners gevaccineerd in " << getNaam() << ".\n";
    }
}
