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
        int hub_counter = 0;
        int centrum_counter = 0;
        for (TiXmlElement* elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement()) {
            std::string elemName = elem->Value();
            // herken element
            int levering_counter = 0;
            int interval_counter = 0;
            int transport_counter = 0;
            int centra_counter = 0;
            int centrumhub_counter = 0;
            int levering;
            int transport;
            int interval;
            if (elemName == "HUB") {
                std::string tag;
                hub_counter = hub_counter + 1;
                for (TiXmlElement* elem_hub = elem->FirstChildElement(); elem_hub != NULL; elem_hub = elem_hub->NextSiblingElement()){
                    tag = elem_hub->Value();
                    if (tag == "levering") {
                        levering_counter = levering_counter + 1;
                        levering = std::atol(fetch_text(elem_hub, errStream).c_str());
                        if (levering<0){
                            errStream << "XML PARTIAL IMPORT: Illegal levering " << levering << "."<< std::endl;
                            endResult = PartialImport;
                        } else {
                            simulatie.setLevering(levering);
                            simulatie.setVaccins(simulatie.getLevering());
                        }
                    }
                    else if(tag == "interval"){
                        interval_counter = interval_counter + 1;
                        interval = std::atol(fetch_text(elem_hub, errStream).c_str());
                        if (interval<0){
                            errStream << "XML PARTIAL IMPORT: Illegal interval " << interval << "."<< std::endl;
                            endResult = PartialImport;
                        } else{
                            simulatie.setInterval(interval);
                        }
                    }
                    else if (tag == "transport"){
                        transport_counter = transport_counter +1;
                        transport= std::atol(fetch_text(elem_hub, errStream).c_str());
                        if (transport < 1){
                            errStream << "XML PARTIAL IMPORT: Illegal transport " << transport << "."<< std::endl;
                            endResult = PartialImport;
                        } else{
                            simulatie.setTransport(transport);
                        }
                    }
                    else if (tag == "CENTRA") {
                        centra_counter = centra_counter + 1;
                        for (TiXmlElement *centrumNaam = elem_hub->FirstChildElement();
                            centrumNaam != NULL; centrumNaam = centrumNaam->NextSiblingElement()) {
                            std::string tagNaam = centrumNaam->Value();
                            if (tagNaam == "centrum") {
                                centrumhub_counter = centrumhub_counter + 1;
                                std::string naam = fetch_text(centrumNaam, errStream);
                                centra1.push_back(naam);
                            } else {
                                errStream << "XML PARTIAL IMPORT: Unexpected tag  in CENTRA" << std::endl;
                                endResult = PartialImport;
                            }
                        }
                    }
                    else{
                        errStream << "XML PARTIAL IMPORT: Unexpected tag in HUB" << std::endl;
                        endResult = PartialImport;
                    }

                }
                if (levering_counter != 1 or interval_counter != 1 or transport_counter != 1 or centra_counter != 1){
                    errStream << "XML PARTIAL IMPORT: HUB has missing or duplicate attributes" << std::endl;
                    endResult = PartialImport;
                }
            } else if (elemName == "VACCINATIECENTRUM") {
                centrum_counter = centrum_counter +1;
                int naam_counter = 0;
                int adres_counter = 0;
                int inwoners_counter = 0;
                int capaciteit_counter = 0;
                int inwoner_aantal;
                int capaciteit;
                std::string naam;
                std::string tag_centrum;
                for (TiXmlElement* elem_centrum = elem->FirstChildElement(); elem_centrum != NULL; elem_centrum = elem_centrum->NextSiblingElement()){
                    tag_centrum = elem_centrum->Value();
                    if (tag_centrum == "naam"){
                        naam_counter = naam_counter + 1;
                        naam = fetch_text(elem_centrum, errStream);
                        if (std::count(centra2.begin(), centra2.end(), naam) != 0){
                            errStream << "XML PARTIAL IMPORT: Centrum " << naam << " already exists."<< std::endl;
                            endResult = PartialImport;
                        }
                        tempCentrum.naam = fetch_text(elem_centrum, errStream);
                    }
                    else if (tag_centrum == "adres"){
                        adres_counter = adres_counter +1;
                        tempCentrum.adres = fetch_text(elem_centrum, errStream);
                    }
                    else if (tag_centrum == "inwoners"){
                        inwoners_counter = inwoners_counter +1;
                        inwoner_aantal = std::atol(fetch_text(elem_centrum, errStream).c_str());
                        if (inwoner_aantal < 0){
                            errStream << "XML PARTIAL IMPORT: Illegal inwoners " << inwoner_aantal << "."<< std::endl;
                            endResult = PartialImport;
                        } else {
                            tempCentrum.inwoners = inwoner_aantal;
                        }
                    }
                    else if (tag_centrum == "capaciteit"){
                        capaciteit_counter = capaciteit_counter +1;
                        capaciteit = std::atol(fetch_text(elem_centrum, errStream).c_str());
                        if (capaciteit < 0){
                            errStream << "XML PARTIAL IMPORT: Illegal capaciteit " << capaciteit << "."<< std::endl;
                            endResult = PartialImport;
                        } else {
                            tempCentrum.capaciteit = capaciteit;
                        }
                    }
                    else{
                        errStream << "XML PARTIAL IMPORT: Unexpected tag in CENTRUM" << std::endl;
                        endResult = PartialImport;
                    }
                }
                if (naam_counter != 1 or adres_counter !=1 or inwoners_counter != 1 or capaciteit_counter !=1){
                    errStream << "XML PARTIAL IMPORT: VACCINATIECENTRUM has missing or duplicate attributes" << std::endl;
                    endResult = PartialImport;
                }
                simulatie.centra.push_back(tempCentrum);
                centra2.push_back(tempCentrum.naam);
            }
            else{
                errStream << "XML PARTIAL IMPORT: Unexpected tag in Simulatie" << std::endl;
                endResult = PartialImport;
            }
        }
        std::sort(centra2.begin(), centra2.end());
        std::sort(centra1.begin(), centra1.end());

        if (centra1 != centra2) {
            errStream << "XML PARTIAL IMPORT: Input file not consistent, problem: Vaccinatiecentra" << std::endl;
            endResult = PartialImport;
        }
        if (hub_counter != 1){
            errStream << "XML PARTIAL IMPORT: Input file not consistent, problem: input file doesn't contain exactly 1 HUB." <<std::endl;
            endResult = PartialImport;
        }
        if (centrum_counter <1){
            errStream << "XML PARTIAL IMPORT: Input file not consistent, problem: input file must atleast contain 1 centrum" << std::endl;
            endResult = PartialImport;
        }
    }
    doc.Clear();
    return endResult;
}
