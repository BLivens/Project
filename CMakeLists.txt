
cmake_minimum_required(VERSION 3.6)
project(Project)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(gtest/include)

# Set Library dir
link_directories(gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp Centrum.cpp Centrum.h HUB.cpp HUB.h main.cpp
        ProjectImporter.cpp ProjectImporter.h ProjectUtils.cpp ProjectExporter.h ProjectExporter.cpp Vaccin.cpp Vaccin.h Simulatie.cpp
        Simulatie.h)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES tinystr.cpp tinyxml.cpp tinyxmlerror.cpp tinyxmlparser.cpp Centrum.cpp Centrum.h HUB.cpp HUB.h ProjectDomainTests.cpp
        ProjectTests.cpp ProjectUtils.cpp ProjectImporter.cpp ProjectImporter.h  ProjectExporter.h ProjectExporter.cpp ProjectInputTests.cpp
        ProjectOutputTests.cpp Vaccin.cpp Vaccin.h)

# Create RELEASE target
add_executable(Project ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(Project_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(Project_debug gtest)
