cmake_minimum_required(VERSION 3.29)

project(
    MankalaEngine
    VERSION 0.1
    DESCRIPTION "Engine used for creating computerized opponents for Mancala variants."
    LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(IS_PROJECT TRUE)
else()
    set(IS_PROJECT FALSE)
endif()

option(BUILD_TESTING "Build the tests" ${IS_PROJECT})
option(BUILD_DOCS "Build the docs" ${IS_PROJECT})

if(${IS_PROJECT})
    include(CTest)
endif()

if(${IS_PROJECT} AND BUILD_DOCS)
    add_subdirectory(docs)
endif()

if(${IS_PROJECT} AND BUILD_TESTING)
    add_subdirectory(test)
    set(CMAKE_CXX_CLANG_TIDY clang-tidy)
    set(CMAKE_CXX_CPPCHECK cppcheck --check-level=exhaustive --enable=warning,style,performance -I include/mankalaengine/ src)
endif()

add_subdirectory(src)
