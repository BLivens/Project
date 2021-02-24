/* ----------------------------------------------------
Alle handelingen die te maken hebben met XML bestanden,
zowel lezen als schrijven. Gebruikt hiervoor tinyxml.
---------------------------------------------------- */

#include "eigXML.h"
#include <iostream>
#include "tinyxml/tinyxml.h"
#include <string>
#include <vector>


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
             int levering = std::atol(elem->Attribute("levering")); // Zodra mogelijk schrijven naar een HUB klasse
             int interval = std::atol(elem->Attribute("interval"));
             int transport = std::atol(elem->Attribute("transport"));
             std::vector<std::string> centra;
             // itereren over de centra om ze aan de lijst toe te voegen.
        }
    }

    doc.Clear();
    return 0;
}

