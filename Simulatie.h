//
// Created by michel on 01.06.21.
//

#ifndef PROJECT_SIMULATIE_H
#define PROJECT_SIMULATIE_H

#include "HUB.h"

class Simulatie {
public:
    /**
    \n ENSURE(properlyInitialized(),"constructor must end in properlyInitialized state");
    */
    Simulatie();
    bool properlyInitialized() const;
    /**
    \n REQUIRE(this->properlyInitialized(), "Simulatie wasn't initialized when calling simuleren");
    \n REQUIRE(dagen>=0, "Dagen must be an integer greater or equal to 0.");
    */
    void simuleren(int dagen, std::ostream &onStream);
    std::vector<Hub*> hubs;
    std::vector<Centrum*> centra;
    std::map<std::string, int> geleverde_vacc;
private:
    Simulatie* _initCheck;
};


#endif //PROJECT_SIMULATIE_H
