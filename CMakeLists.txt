#=============================================================================
# SPDX-FileCopyrightText: 2024 João Gouveia <jtalonegouveia@gmail.com>
# SPDX-FileCopyrightText: 2025 Srisharan V S <srisharan.psgtech@gmail.com>
#
# SPDX-License-Identifier: GPL-3.0-or-later
#=============================================================================

cmake_minimum_required(VERSION 3.23)

project(
    MankalaEngine
    VERSION 1.1
    DESCRIPTION "Engine used for creating computerized opponents for Mancala variants."
    LANGUAGES CXX)

set(QT_MIN_VERSION "6.5.0")
set(KF6_DEP_VERSION "6.0.0")
set(QT_MAJOR_VERSION "6")
find_package(Qt6 COMPONENTS Test)

find_package(ECM 6.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH})

include(KDEInstallDirs6)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(KDECMakeSettings NO_POLICY_SCOPE)
include(ECMMarkNonGuiExecutable)

find_package(KF6 ${KF6_DEP_VERSION}
    REQUIRED COMPONENTS
        I18n
)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(IS_PROJECT TRUE)
else()
    set(IS_PROJECT FALSE)
endif()

add_definitions(-DTRANSLATION_DOMAIN="mankalaengine")

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

ki18n_install(po)

