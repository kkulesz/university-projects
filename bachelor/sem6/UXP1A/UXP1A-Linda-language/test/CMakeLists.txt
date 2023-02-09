enable_testing()
find_package(Boost COMPONENTS unit_test_framework  REQUIRED)
include_directories (${Boost_INCLUDE_DIRS})

file(GLOB TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)

foreach(testSrc ${TEST_SRCS})
    get_filename_component(testName ${testSrc} NAME_WE)
    ADD_EXECUTABLE(${testName} $<TARGET_OBJECTS:linda_objects>
            ${testSrc})
    target_link_libraries(${testName} ${Boost_LIBRARIES} )
    set_target_properties(${testName} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_SOURCE_DIR}/testBin)
    add_test(NAME ${testName}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/testBin
            COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/testBin/${testName} )
endforeach(testSrc)
