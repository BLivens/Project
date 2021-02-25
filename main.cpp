#include <iostream>
#include "HUB.h"



void simuleren(int dagen, Hub simHub) {
    int dag = 0;
    while (dag < dagen) {
        if (dag % simHub.interval == 0) {
            simHub.vaccins = simHub.vaccins + simHub.transport;
        }

        // simHub.simulateTransport();


        for (int i = 0; i < simHub.centra.size(); i++) {
          simHub.centra.at(i).vaccineren();
        }
        dag++;
    }
}


int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
