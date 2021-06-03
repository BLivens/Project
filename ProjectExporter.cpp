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
        outfile << "  -> " << (*simulatie.centra.at(i))->getNaam() << " (" <<  (*simulatie.centra[i])->getVoorraad() << " vaccins)" << std::endl;
    }
    outfile << std::endl;

    for(unsigned int i = 0; i < simulatie.centra.size(); i++) {
        outfile << (*simulatie.centra[i])->getNaam() << ": " << (*simulatie.centra[i])->getGevacineerden() << " gevaccineerd, nog "
            << (*simulatie.centra[i])->getInwoners() - (*simulatie.centra[i])->getGevacineerden() << " inwoners niet gevaccineerd" << std::endl;
    }

    outfile.close();
    return endResult;
}

SuccessEnum2 ProjectExporter::graphic_impression(const char *outputfilename, std::ostream &errStream, Hub &simulatie) {

    std::ofstream outfile(outputfilename);
    SuccessEnum2 endResult = ExportSuccess;
    if (!outfile.is_open()) {
        errStream << "Can't open " << outputfilename << std::endl;
        endResult = ExportAborted;
        return endResult;
    }

    for(unsigned int i = 0; i < simulatie.centra.size(); i++) {
        outfile << (*simulatie.centra[i])->getNaam() << ":" <<  std::endl;

        outfile << "\t" << "- vaccins" << "\t" << "[";
        int percent_vacc = (double) (*simulatie.centra[i])->getVoorraad()/ (double) (*simulatie.centra[i])->getCapaciteit()*100;

        int bars_vacc = percent_vacc/5;
        int space_vacc = 20-bars_vacc;
        for(int j = 0; j<bars_vacc; j++){
            outfile << "=";
        }
        for(int j = 0; j<space_vacc; j++){
            outfile << " ";
        }
        outfile << "]" << " " << percent_vacc << "%" << std::endl;

        outfile << "\t" << "- gevaccineerd" << "\t" << "[";
        int percent_gevac = (double) (*simulatie.centra[i])->getGevacineerden()/ (double) (*simulatie.centra[i])->getInwoners()*100;
        int bars_gevac = percent_gevac/5;
        int space_gevac = 20-bars_gevac;
        for(int j = 0; j<bars_gevac; j++){
            outfile << "=";
        }
        for(int j = 0; j<space_gevac; j++){
            outfile << " ";
        }
        outfile << "]" << " " << percent_gevac << "%" << std::endl;

    }
    outfile.close();

    return endResult;
}
