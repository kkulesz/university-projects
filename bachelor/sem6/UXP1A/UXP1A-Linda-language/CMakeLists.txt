cmake_minimum_required(VERSION 3.17)
project(uxp1a-linda)

set(CMAKE_CXX_STANDARD 20)

find_package(Boost COMPONENTS unit_test_framework  REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
FILE(GLOB_RECURSE LINDA_SOURCES src/*/*.cpp)
ADD_LIBRARY(linda_objects OBJECT ${LINDA_SOURCES})
ADD_EXECUTABLE(linda-server $<TARGET_OBJECTS:linda_objects> src/linda-server.cpp)
target_link_libraries(linda-server ${Boost_LIBRARIES} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
ENABLE_TESTING()
ADD_SUBDIRECTORY(test)


ADD_EXECUTABLE(linda-test $<TARGET_OBJECTS:linda_objects> src/linda-client.cpp)