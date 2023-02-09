# cmake_minimum_required(VERSION <specify CMake version here>)
project(PROJEKT)

set(CMAKE_CXX_STANDARD 20)

add_executable(PROJEKT src/main.cpp src/utilities.cpp src/bruteForce.cpp src/creatingGroupsWithLast.cpp src/startFromBeg.cpp include/startFromBeg.h src/fast4Create.cpp)