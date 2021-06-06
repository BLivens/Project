#include "ProjectImporter.h"

//Auxiliary function for internal use only
// opmerking: fetch_text is dezelfde functie als gebruikt in TicTacToe21 door professor Demeyer
const std::string fetch_text(TiXmlNode *pElement, std::ostream& errStream) {
    if (pElement == NULL) return "";
    TiXmlNode *elemNode = pElement->FirstChild();
    if (elemNode == NULL) return "";
    TiXmlText* text = elemNode->ToText();
    if(text == NULL) return "";
    return text->Value();
}

SuccessEnum ProjectImporter::importProject(const char *inputfilename, std::ostream &errStream, Simulatie &simulatie) {

    std::vector<std::string> centra1; // een lijstje met de namen van de centra om na te kijken of de XML wel consistent is
    std::vector<std::string> centra2;
    std::vector<std::vector<std::string> > centra3;

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
            int vaccin_counter = 0;
            int centra_counter = 0;
            int centrumhub_counter = 0;
            if (elemName == "HUB") {
                Hub* tempHub = new Hub;
                std::string tag;
                hub_counter = hub_counter + 1;
                std::vector<std::string> tempVec;
                for (TiXmlElement* elem_hub = elem->FirstChildElement(); elem_hub != NULL; elem_hub = elem_hub->NextSiblingElement()){
                    tag = elem_hub->Value();

                    if (tag == "VACCIN") {
                        vaccin_counter = vaccin_counter + 1;
                        Vaccin* tempvac = new Vaccin;
                        std::string type;
                        std::string tag_vacc;
                        unsigned int levering_counter = 0;
                        unsigned int interval_counter = 0;
                        unsigned int transport_counter = 0;
                        int hernieuwing_counter = 0;
                        int typecounter = 0;
                        int temperatuur_counter = 0;
                        int levering;
                        int interval;
                        int transport;
                        int hernieuwing;
                        int temperatuur;
                        for (TiXmlElement* elem_vacc = elem_hub->FirstChildElement(); elem_vacc != NULL; elem_vacc = elem_vacc->NextSiblingElement()) {
                            tag_vacc = elem_vacc->Value();
                            if (tag_vacc == "type") {
                                typecounter ++;
                                type = fetch_text(elem_vacc, errStream);
                                if (type.empty()){
                                    errStream << "XML PARTIAL IMPORT: Illegal type " << type << "."<< std::endl;
                                    endResult = PartialImport;
                                } else {
                                    tempvac->setType(type);
                                }
                            } else if (tag_vacc == "levering") {
                                levering_counter++;
                                levering = std::atol(fetch_text(elem_vacc, errStream).c_str());
                                if (levering < 0) {
                                    errStream << "XML PARTIAL IMPORT: Illegal levering " << levering << "."
                                              << std::endl;
                                    endResult = PartialImport;
                                } else {
                                    tempvac->setLevering(levering);
                                }
                            } else if (tag_vacc == "interval") {
                                interval_counter++;
                                interval = std::atol(fetch_text(elem_vacc, errStream).c_str());
                                if (interval <= 0) {
                                    errStream << "XML PARTIAL IMPORT: Illegal interval " << interval << "."
                                              << std::endl;
                                    endResult = PartialImport;
                                } else {
                                    tempvac->setInterval(interval);
                                }
                            } else if (tag_vacc == "transport") {
                                transport_counter++;
                                transport = std::atol(fetch_text(elem_vacc, errStream).c_str());
                                if (transport < 1) {
                                    errStream << "XML PARTIAL IMPORT: Illegal transport " << transport << "."
                                              << std::endl;
                                    endResult = PartialImport;
                                } else {
                                    tempvac->setTransport(transport);
                                }
                            } else if (tag_vacc == "hernieuwing") {
                                hernieuwing_counter++;
                                hernieuwing = std::atol(fetch_text(elem_vacc, errStream).c_str());
                                if (hernieuwing < 0) {
                                    errStream << "XML PARTIAL IMPORT: Illegal hernieuwing " << hernieuwing << "."
                                              << std::endl;
                                    endResult = PartialImport;
                                } else {
                                    tempvac->setHernieuwing(hernieuwing);
                                }
                            } else if (tag_vacc == "temperatuur") {
                                temperatuur_counter++;
                                temperatuur = std::atol(fetch_text(elem_vacc, errStream).c_str());
                                tempvac->setTemperatuur(temperatuur);
                            }
                            else{
                                errStream << "XML PARTIAL IMPORT: Unexpected tag in VACCIN." << std::endl;
                                endResult = PartialImport;
                            }

                        }
                        if (typecounter != 1 or hernieuwing_counter != 1 or levering_counter != 1 or interval_counter != 1 or transport_counter != 1){
                            errStream << "XML PARTIAL IMPORT: VACCIN has missing or duplicate attributes." << std::endl;
                            endResult = PartialImport;
                        }
                        tempHub->vaccins.push_back(tempvac);
                    }

                    else if (tag == "CENTRA") {
                        centra_counter = centra_counter + 1;
                        for (TiXmlElement *centrumNaam = elem_hub->FirstChildElement();
                            centrumNaam != NULL; centrumNaam = centrumNaam->NextSiblingElement()) {
                            std::string tagNaam = centrumNaam->Value();
                            if (tagNaam == "centrum") {
                                centrumhub_counter = centrumhub_counter + 1;
                                std::string naam = fetch_text(centrumNaam, errStream);
                                // check of element al aanwezig was in vorige hub
                                if (std::find(centra1.begin(), centra1.end(), naam) == centra1.end()){
                                    // indien niet
                                    centra1.push_back(naam);
                                }
                                tempVec.push_back(naam);
                            } else {
                                errStream << "XML PARTIAL IMPORT: Unexpected tag in CENTRA." << std::endl;
                                endResult = PartialImport;
                            }
                        }
                    }
                    else{
                        errStream << "XML PARTIAL IMPORT: Unexpected tag in HUB." << std::endl;
                        endResult = PartialImport;
                    }
                }
                if (vaccin_counter < 1 or centra_counter != 1 or centrumhub_counter < 1){
                    errStream << "XML PARTIAL IMPORT: Hub has missing or duplicate attributes." << std::endl;
                    endResult = PartialImport;
                }
                centra3.push_back(tempVec);
                simulatie.hubs.push_back(tempHub);

            } else if (elemName == "VACCINATIECENTRUM") {
                Centrum* tempCentrum = new Centrum;
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
                        tempCentrum->setNaam(fetch_text(elem_centrum, errStream));
                    }
                    else if (tag_centrum == "adres"){
                        adres_counter = adres_counter +1;
                        tempCentrum->setAdres(fetch_text(elem_centrum, errStream));
                    }
                    else if (tag_centrum == "inwoners"){
                        inwoners_counter = inwoners_counter +1;
                        inwoner_aantal = std::atol(fetch_text(elem_centrum, errStream).c_str());
                        if (inwoner_aantal < 0){
                            errStream << "XML PARTIAL IMPORT: Illegal inwoners " << inwoner_aantal << "."<< std::endl;
                            endResult = PartialImport;
                        } else {
                            tempCentrum->setInwoners(inwoner_aantal);
                        }
                    }
                    else if (tag_centrum == "capaciteit"){
                        capaciteit_counter = capaciteit_counter +1;
                        capaciteit = std::atol(fetch_text(elem_centrum, errStream).c_str());
                        if (capaciteit < 0){
                            errStream << "XML PARTIAL IMPORT: Illegal capaciteit " << capaciteit << "."<< std::endl;
                            endResult = PartialImport;
                        } else {
                            tempCentrum->setCapaciteit(capaciteit);
                        }
                    }
                    else{
                        errStream << "XML PARTIAL IMPORT: Unexpected tag in VACCINATIECENTRUM." << std::endl;
                        endResult = PartialImport;
                    }
                }
                if (naam_counter != 1 or adres_counter !=1 or inwoners_counter != 1 or capaciteit_counter !=1){
                    errStream << "XML PARTIAL IMPORT: VACCINATIECENTRUM has missing or duplicate attributes." << std::endl;
                    endResult = PartialImport;
                }
                simulatie.centra.push_back(tempCentrum);
                centra2.push_back(tempCentrum->getNaam());
            }
            else{
                errStream << "XML PARTIAL IMPORT: Unexpected tag in Simulatie." << std::endl;
                endResult = PartialImport;
            }
        }
        std::sort(centra2.begin(), centra2.end());
        std::sort(centra1.begin(), centra1.end());


        if (hub_counter < 1){
            errStream << "XML PARTIAL IMPORT: Input file not consistent, problem: input file needs to contain atleast one hub." <<std::endl;
            endResult = PartialImport;
        }
        if (centra1 != centra2) {
            errStream << "XML PARTIAL IMPORT: Input file not consistent, problem: Vaccinatiecentra." << std::endl;
            endResult = PartialImport;
        }
        if (centrum_counter <1){
            errStream << "XML PARTIAL IMPORT: Input file not consistent, problem: input file must at least contain 1 centrum." << std::endl;
            endResult = PartialImport;
        }
    }
    for (unsigned int i = 0; i < simulatie.centra.size(); i++){
        for (unsigned int j = 0; j<simulatie.hubs.size(); j++){
            if (std::find(centra3[j].begin(), centra3[j].end(), simulatie.centra[i]->getNaam()) != centra3[j].end()){
                // indien wel gevonden
                Centrum** double_p = &simulatie.centra[i];
                simulatie.hubs[j]->centra.push_back(double_p);
            }
        }
    }

    for (unsigned int i = 0; i < simulatie.hubs.size(); i++) {
        for (unsigned int j = 0; j < simulatie.hubs[i]->vaccins.size();j++){
            std::string vacc_name = simulatie.hubs[i]->vaccins[j]->getType();
            for (unsigned int k = 0; k < simulatie.hubs[i]->centra.size(); k++){
                bool aanwezig = false;
                for (unsigned int l = 0; l < (*simulatie.hubs[i]->centra[k])->vaccins.size(); l++){
                    if ((*simulatie.hubs[i]->centra[k])->vaccins[l]->getType() == vacc_name) {
                        aanwezig = true;
                    }
                }
                if (aanwezig == false){
                    Vaccin* tempvac = new Vaccin;
                    tempvac->setType(simulatie.hubs[i]->vaccins[j]->getType());
                    tempvac->setLevering(simulatie.hubs[i]->vaccins[j]->getLevering());
                    tempvac->setInterval(simulatie.hubs[i]->vaccins[j]->getInterval());
                    tempvac->setTransport(simulatie.hubs[i]->vaccins[j]->getTransport());
                    tempvac->setHernieuwing(simulatie.hubs[i]->vaccins[j]->getHernieuwing());
                    tempvac->setTemperatuur(simulatie.hubs[i]->vaccins[j]->getTemperatuur());
                    (*simulatie.hubs[i]->centra[k])->vaccins.push_back(tempvac);
                }

            }
        }
    }


    doc.Clear();
    return endResult;
}
