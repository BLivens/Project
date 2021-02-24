#include <vector>
#include <string>
#include "Centrum.h"


#ifndef PROJECT_HUB_H
#define PROJECT_HUB_H

class Hub {
public:
    int levering;
    int interval;
    int transport;
    std::vector<Centrum> centra;
};

#endif //PROJECT_HUB_H
