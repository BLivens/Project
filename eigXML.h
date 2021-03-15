#include <iostream>
#include "tinyxml.h"
#include <string>
#include <vector>
#include "HUB.h"
#include "Centrum.h"
#include <algorithm>
#include <fstream>

#ifndef PROJECT_eigXML_H
#define PROJECT_eigXML_H

Hub inlezen(FILE *input);
int schrijven(std::string file, Hub outHub);


#endif //PROJECT_eigXML_H
