cmake_minimum_required(VERSION 3.29)

project(
    MankalaEngine
    VERSION 0.1
    DESCRIPTION "Engine used for creating computerized opponents for Mancala variants."
    LANGUAGES CXX)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(IS_PROJECT TRUE)
else()
    set(IS_PROJECT FALSE)
endif()

option(BUILD_TESTING "Build the tests" ${IS_PROJECT})

if(${IS_PROJECT})
    include(CTest)
endif()

add_subdirectory(src)

if(${IS_PROJECT} AND BUILD_TESTING)
    add_subdirectory(test)
endif()
