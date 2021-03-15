//
// Created by michel on 14.03.21.
//

#include "ProjectImporter.h"


const std::string fetch_text(TiXmlNode *pElement, std::ostream& errStream) {
    if (pElement == NULL) return "";
    TiXmlNode *elemNode = pElement->FirstChild();
    if (elemNode == NULL) return "";
    TiXmlText* text = elemNode->ToText();
    if(text == NULL) return "";
    return text->Value();
}

SuccessEnum ProjectImporter::importProject(const char *inputfilename, std::ostream &errStream, Hub &simulatie) {
    Centrum tempCentrum;
    std::vector<std::string> centra1; // een lijstje met de namen van de centra om na te kijken of de XML wel consistent is
    std::vector<std::string> centra2;

    TiXmlDocument doc;
    SuccessEnum endResult = Success;
    if (!doc.LoadFile(inputfilename)) {
        errStream << "XML IMPORT ABORTED: " << doc.ErrorDesc() << std::endl;
        return ImportAborted;
    }
    TiXmlElement* root = doc.FirstChildElement();
    if (root == NULL) {
        errStream << "Failed to load File: no root element." << std::endl;
        endResult = PartialImport;
    }
    else {

        for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
            std::string elemName = elem->Value();
            // herken element

            if (elemName == "HUB") {
                TiXmlNode *elem_levering;
                TiXmlNode *elem_interval;
                TiXmlNode *elem_transport;
                TiXmlNode *elem_centra;
                elem_levering = elem->FirstChild("levering");
                elem_interval = elem->FirstChild("interval");
                elem_transport = elem->FirstChild("transport");
                elem_centra = elem->FirstChild("CENTRA");
                int levering; int interval; int transport;
                if (elem_levering == NULL) {
                    errStream << "XML PARTIAL IMPORT: Expected <levering> ... </levering>. in HUB" << std::endl;
                    endResult = PartialImport;
                    levering = 1;
                }
                else{
                    levering = std::atol(fetch_text(elem_levering, errStream).c_str());
                }
                if (elem_interval == NULL) {
                    errStream << "XML PARTIAL IMPORT: Expected <interval> ... </interval>. in HUB" << std::endl;
                    endResult = PartialImport;
                    interval = 1;
                }
                else{
                    interval = std::atol(fetch_text(elem_interval, errStream).c_str());
                }
                if (elem_transport == NULL) {
                    errStream << "XML PARTIAL IMPORT: Expected <transport> ... </transport>. in HUB" << std::endl;
                    endResult = PartialImport;
                    transport = 1;
                }
                else{
                    transport= std::atol(fetch_text(elem_transport, errStream).c_str());
                }


                simulatie.setLevering(levering); // Zodra die bestaat schrijven naar een HUB klasse
                simulatie.setVaccins(simulatie.getLevering());
                simulatie.setInterval(interval);
                simulatie.setTransport(transport);

                for (TiXmlElement* centrumNaam = elem_centra->FirstChildElement(); centrumNaam != NULL; centrumNaam = centrumNaam->NextSiblingElement()) {
                    std::string naam = fetch_text(centrumNaam, errStream);
                    centra1.push_back(naam);
                }
            } else if (elemName == "VACCINATIECENTRUM") {
                TiXmlNode *Naam;
                TiXmlNode *Adres;
                TiXmlNode *Inwoners;
                TiXmlNode *Capaciteit;
                Naam = elem->FirstChild("naam");
                Adres = elem->FirstChild("adres");
                Inwoners = elem->FirstChild("inwoners");
                Capaciteit = elem->FirstChild("capaciteit");


                tempCentrum.naam = fetch_text(Naam, errStream);
                tempCentrum.adres = fetch_text(Adres, errStream);
                tempCentrum.inwoners = std::atol(fetch_text(Inwoners, errStream).c_str());
                tempCentrum.capaciteit = std::atol(fetch_text(Capaciteit, errStream).c_str());

                simulatie.centra.push_back(tempCentrum);
                centra2.push_back(tempCentrum.naam);
            }
        }
        std::sort(centra2.begin(), centra2.end());
        std::sort(centra1.begin(), centra1.end());

        if (centra1 != centra2) {
            std::cerr << "Input File not consistent. problem: Vaccinatiecentra" << std::endl;
        }
    }
    doc.Clear();
    return endResult;
}
