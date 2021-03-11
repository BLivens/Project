
cmake_minimum_required(VERSION 3.6)
project(Project)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-Wall -Werror")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

add_executable(Project main.cpp HUB.cpp HUB.h Centrum.cpp Centrum.h DesignByContract.h)