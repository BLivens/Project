#include <string>
#include <iostream>

#ifndef PROJECT_CENTRUM_H
#define PROJECT_CENTRUM_H

class Centrum {
public:
    std::string naam;
    std::string adres;
    int inwoners;
    int capaciteit;
    int vaccins;
    int gevacineerden;
    void vaccineren();
};

#endif //PROJECT_CENTRUM_H
