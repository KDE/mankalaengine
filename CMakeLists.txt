cmake_minimum_required(VERSION 3.23)

project(
    MankalaEngine
    VERSION 1.1
    DESCRIPTION "Engine used for creating computerized opponents for Mancala variants."
    LANGUAGES CXX)

find_package(Qt6 COMPONENTS Test)

find_package(ECM 6.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs6)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings NO_POLICY_SCOPE)
include(ECMMarkNonGuiExecutable)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(IS_PROJECT TRUE)
else()
    set(IS_PROJECT FALSE)
endif()

option(BUILD_TESTING "Build the tests" ${IS_PROJECT})
option(BUILD_DOCS "Build the docs" ${IS_PROJECT})
option(BUILD_EXAMPLES "Build the examples" ${IS_PROJECT})
option(BUILD_BENCHMARK "Build the engine comparison utility" ${IS_PROJECT})
option(BUILD_LINTING "Run the linting utilities when building" ${IS_PROJECT})

if (${IS_PROJECT} AND BUILD_LINTING)
    find_program(CLANG_TIDY NAMES "clang-tidy")
    if(CLANG_TIDY)
        set(CLANG_TIDY_COMMAND "${CLANG_TIDY}" "-p" "${CMAKE_BINARY_DIR}")
    endif()

    find_program(CPPCHECK NAMES "cppcheck")
    if(CPPCHECK)
      set(
          CPPCHECK_COMMAND
          "${CPPCHECK}"
          "--enable=warning,style,performance"
          "-I include/mankalaengine/")
    endif()
endif()

if(${IS_PROJECT} AND BUILD_TESTING AND Qt6_FOUND)
    add_subdirectory(test)
endif()

if(${IS_PROJECT} AND BUILD_BENCHMARK)
    add_subdirectory(benchmark)
endif()

if(${IS_PROJECT} AND BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(${IS_PROJECT} AND BUILD_DOCS)
    add_subdirectory(docs)
endif()

add_subdirectory(src)
