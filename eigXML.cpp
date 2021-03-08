/* ----------------------------------------------------
Alle handelingen die te maken hebben met XML bestanden,
zowel lezen als schrijven. Gebruikt hiervoor tinyxml.
---------------------------------------------------- */

#include "eigXML.h"


Hub inlezen(FILE *input) {
    Centrum tempCentrum;
    Hub outHub;
    std::vector<std::string> centra1; // een lijstje met de namen van de centra om na te kijken of de XML wel consistent is
    std::vector<std::string> centra2;

    TiXmlDocument doc;
    if (!doc.LoadFile(input)) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return outHub;
    }
    TiXmlElement* root = doc.FirstChildElement();
    if (root == NULL) {
        std::cerr << "Failed to load File: no root element." << std::endl;
        doc.Clear();
        return outHub;
    }

    for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();


        if (elemName == "HUB") {
            outHub.setVaccins(std::atol(elem->Attribute("levering"))); // Zodra die bestaat schrijven naar een HUB klasse
            outHub.setInterval(std::atol(elem->Attribute("interval")));
            outHub.setTransport(std::atol(elem->Attribute("transport")));

            for (TiXmlElement* centrumNaam = elem->FirstChildElement(); centrumNaam != NULL; centrumNaam = centrumNaam->NextSiblingElement()) {
                centra1.push_back(centrumNaam->Attribute("centrum"));
            }
        } else if (elemName == "VACCINATIECENTRUM") {
            tempCentrum.naam = elem->Attribute("naam");
            tempCentrum.adres = elem->Attribute("adres");
            tempCentrum.inwoners = std::atol(elem->Attribute("inwoners"));
            tempCentrum.capaciteit = std::atol(elem->Attribute("capaciteit"));

            outHub.centra.push_back(tempCentrum);
            centra2.push_back(tempCentrum.naam);
        }
    }
    std::sort(centra2.begin(), centra2.end());
    std::sort(centra1.begin(), centra1.end());

    if (centra1 != centra2) {
        std::cerr << "Input File not consistent. problem: Vaccinatiecentra" << std::endl;
    }
    doc.Clear();
    return outHub;
}

int schrijven(std::string file, Hub outHub) {
    std::ofstream outfile;
    outfile.open("file"); // stomme error, komt er op neer, files worden niet als string meegegeven.

    outfile << "Hub: (" << outHub.getVaccins()<< " vaccins)\n";
    if (!outfile.is_open()) {
        std::cerr << "Umable open file" << file << std::endl;
        return 1;
    }

    for (unsigned int i = 0; i < outHub.centra.size(); i++){
        outfile << "  -> " << outHub.centra.at(i).naam << " (" << outHub.centra.at(i).vaccins << " vaccins)\n";
    }

    outfile << std::endl;

    for (unsigned int i = 0; i < outHub.centra.size(); i++){
        outfile << outHub.centra.at(i).naam << ": " << outHub.centra.at(i).gevacineerden << " gevacineerden, nog "
            << outHub.centra.at(i).inwoners - outHub.centra.at(i).gevacineerden << " inwoners niet gevaccineerd";
    }

    outfile.close();
    return 0;

}



