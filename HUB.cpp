#include "HUB.h"
#include <vector>
#include <string>

class HUB {
public:
    int levering;
    int interval;
    int transport;
    std::vector<std::string> centra; // Misschien moeten we hier i.p.v. de namen effectief de centra (van klasse centrum) inzetten.
};
