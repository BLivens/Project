/* ----------------------------------------------------
Alle handelingen die te maken hebben met XML bestanden,
zowel lezen als schrijven. Gebruikt hiervoor tinyxml.
---------------------------------------------------- */

#include "eigXML.h"


int inlezen(FILE *input) {
    TiXmlDocument doc;
    if (!doc.LoadFile(input)) {
        std::cerr << doc.ErrorDesc() << std::endl;
        return 1;
    }
    TiXmlElement* root = doc.FirstChildElement();
    if (root == NULL) {
        std::cerr << "Failed to load File: no root element." << std::endl;
        doc.Clear();
        return 1;
    }

    std::vector<Centrum> vacCentra;
    Centrum tempCentrum;
    Hub outHub;
    std::vector<std::string> centra1; // een lijstje met de namen van de centra om na te kijken of de XML wel consistent is
    std::vector<std::string> centra2;

    for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();


        if (elemName == "HUB") {
            outHub.levering = std::atol(elem->Attribute("levering")); // Zodra die bestaat schrijven naar een HUB klasse
            outHub.interval = std::atol(elem->Attribute("interval"));
            outHub.transport = std::atol(elem->Attribute("transport"));

            for (TiXmlElement* centrumNaam = elem->FirstChildElement(); centrumNaam != NULL; centrumNaam = centrumNaam->NextSiblingElement()) {
                centra1.push_back(centrumNaam->Attribute("centrum"));
            }
        } else if (elemName == "VACCINATIECENTRUM") {
            tempCentrum.naam = elem->Attribute("naam");
            tempCentrum.adres = elem->Attribute("adres");
            tempCentrum.inwoners = std::atol(elem->Attribute("inwoners"));
            tempCentrum.capaciteit = std::atol(elem->Attribute("capaciteit"));

            vacCentra.push_back(tempCentrum);
            centra2.push_back(tempCentrum.naam);
        }
    }
    std::sort(centra2.begin(), centra2.end());
    std::sort(centra1.begin(), centra1.end());

    if (centra1 != centra2) {
        std::cerr << "Input File not consistent. probleem: Vaccinatiecentra" << std::endl;
    }

    doc.Clear();
    return 0;
}
