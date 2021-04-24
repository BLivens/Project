//
// Created by michel on 14.03.21.
//

#include "ProjectExporter.h"


SuccessEnum2 ProjectExporter::exportProject(const char *outputfilename, std::ostream &errStream, Hub &simulatie) {

    std::ofstream outfile(outputfilename);
    SuccessEnum2 endResult = ExportSuccess;
    if (!outfile.is_open()) {
        errStream << "Unable to open file: " << outputfilename << std::endl;
        endResult = ExportAborted;
        return endResult;
    }

    outfile << "Hub (" << simulatie.getVoorraad() << " vaccins)" << std::endl;
    for(unsigned int i = 0; i < simulatie.centra.size(); i++) {
        outfile << "  -> " << simulatie.centra.at(i)->getNaam() << " (" <<  simulatie.centra[i]->getVaccins() << " vaccins)" << std::endl;
    }
    outfile << std::endl;

    for(unsigned int i = 0; i < simulatie.centra.size(); i++) {
        outfile << simulatie.centra[i]->getNaam() << ": " << simulatie.centra[i]->getGevacineerden() << " gevaccineerd, nog "
            << simulatie.centra[i]->getInwoners() - simulatie.centra[i]->getGevacineerden() << " inwoners niet gevaccineerd" << std::endl;
    }

    outfile.close();
    return endResult;
}
