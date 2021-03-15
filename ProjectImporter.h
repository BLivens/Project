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
#include <algorithm>
#include <fstream>


enum SuccessEnum {ImportAborted, PartialImport, Success};


class ProjectImporter {
public:
    SuccessEnum importProject(const char * inputfilename, std::ostream& errStream, Hub& simulatie);
};


#endif //PROJECT_PROJECTIMPORTER_H
