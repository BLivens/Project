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

    for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
        std::string elemName = elem->Value();

        if (elemName == "HUB") {
            Hub outhub;
            outhub.levering = std::atol(elem->Attribute("levering")); // Zodra die bestaat schrijven naar een HUB klasse
            outhub.interval = std::atol(elem->Attribute("interval"));
            outhub.transport = std::atol(elem->Attribute("transport"));

            std::vector<std::string> centra; // een lijstje met de namen van de centra om na te kijken of de XML wel consistent is
            for (TiXmlElement* centrumNaam = elem->FirstChildElement(); centrumNaam != NULL; centrumNaam = centrumNaam->NextSiblingElement()) {
                centra.push_back(centrumNaam->Attribute("centrum"));
            }
        }
        if (elemName == "VACCINATIECENTRUM") {

        }
    }

    doc.Clear();
    return 0;
}
