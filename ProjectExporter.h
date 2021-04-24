//
// Created by michel on 14.03.21.
//


#ifndef PROJECT_PROJECTEXPORTER_H
#define PROJECT_PROJECTEXPORTER_H

#include <iostream>
#include <string>
#include <vector>
#include "HUB.h"
#include "Centrum.h"
#include <algorithm>
#include <fstream>



enum SuccessEnum2 {ExportAborted, PartialExport, ExportSuccess};


class ProjectExporter {
public:
    static SuccessEnum2 exportProject(const char * outputfilename, std::ostream& errStream, Hub& simulatie);
    static SuccessEnum2 graphic_impression(const char * outputfilename, std::ostream& errStream, Hub& simulatie);
};


#endif //PROJECT_PROJECTEXPORTER_H
