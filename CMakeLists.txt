cmake_minimum_required(VERSION 3.23)

project(
    MankalaEngine
    VERSION 0.1
    DESCRIPTION "Engine used for creating computerized opponents for Mancala variants."
    LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_CXX_VISIBILITY_INLINES_HIDDEN TRUE)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(IS_PROJECT TRUE)
else()
    set(IS_PROJECT FALSE)
endif()

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
option(BUILD_TESTING "Build the tests" ${IS_PROJECT})
option(BUILD_DOCS "Build the docs" ${IS_PROJECT})
option(BUILD_EXAMPLES "Build the examples" ${IS_PROJECT})

if(${IS_PROJECT})
    include(CTest)
endif()

if(${IS_PROJECT} AND BUILD_TESTING)
    find_program(CLANG_TIDY NAMES "clang-tidy")
    if(CLANG_TIDY)
        set(CLANG_TIDY_COMMAND "${CLANG_TIDY}" "-p" "${CMAKE_BINARY_DIR}")
    endif()

    find_program(CPPCHECK NAMES "cppcheck")
    if(CPPCHECK)
      set(
          CPPCHECK_COMMAND
          "${CPPCHECK}"
          "--check-level=exhaustive"
          "--enable=warning,style,performance"
          "-I include/mankalaengine/")
    endif()

    add_subdirectory(test)
    add_subdirectory(benchmark)
endif()

if(${IS_PROJECT} AND BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

if(${IS_PROJECT} AND BUILD_DOCS)
    add_subdirectory(docs)
endif()

add_subdirectory(src)
