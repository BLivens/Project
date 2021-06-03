//
// Created by michel on 14.03.21.
//


#ifndef PROJECT_PROJECTIMPORTER_H
#define PROJECT_PROJECTIMPORTER_H

#include <iostream>
#include "tinyxml.h"
#include <string>
#include <vector>
#include "HUB.h"
#include "Centrum.h"
#include "Simulatie.h"
#include <algorithm>
#include <fstream>


enum SuccessEnum {ImportAborted, PartialImport, Success};


class ProjectImporter {
public:
    /**
    // Read an XML description of a simulatie from inputfilename.
    // If errors occur, report them on errStream.
    // Return whether succesful in the errorcode:
    //	- ImportAborted =  simulatie is unchanged; reason for abortion is reported on errStream
    //  - PartialImport = Some semantic errors reported on errStream; state is partially imported and simulatie might have changed
    //  - Succes = No importer errors; no errors reported
    //\n REQUIRE(simulatie->properlyInitialized(), "simulatie wasn't initialized when passed to ProjectImporter::importProject");
    //
    */
    static SuccessEnum importProject(const char * inputfilename, std::ostream& errStream, Simulatie& simulatie);
};


#endif //PROJECT_PROJECTIMPORTER_H
