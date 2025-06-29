set(
    HEADER_LIST
    "../include/mankalaengine/mankalaengine.h"
    "../include/mankalaengine/rules.h"
    "../include/mankalaengine/bohnenspielrules.h"
    "../include/mankalaengine/owarerules.h"
    "../include/mankalaengine/pallangulirules.h"
    "../include/mankalaengine/kalahrules.h"
    "../include/mankalaengine/moveselection.h"
    "../include/mankalaengine/variantdescriptions.h")

set(
    PUBLIC_HEADER_LIST
    "${HEADER_LIST}"
    "../include/mankalaengine/mankalaengine_export.h")

add_library(
    MankalaEngine
    mankalaengine.cpp
    rules.cpp
    bohnenspielrules.cpp
    owarerules.cpp
    pallangulirules.cpp
    kalahrules.cpp
    moveselection.cpp
    ${HEADER_LIST})

include(GenerateExportHeader)
generate_export_header(MankalaEngine)
file(
    COPY
    ${CMAKE_CURRENT_BINARY_DIR}/mankalaengine_export.h
    DESTINATION
    ${PROJECT_SOURCE_DIR}/include/mankalaengine)

target_include_directories(
    MankalaEngine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/mankalaengine>
    $<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR}/mankalaengine>)

set_target_properties(MankalaEngine PROPERTIES 
    PUBLIC_HEADER "${PUBLIC_HEADER_LIST}"
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)
if(CLANG_TIDY_COMMAND)
    set_target_properties(MankalaEngine PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
endif()
if(CPPCHECK_COMMAND)
    set_target_properties(MankalaEngine PROPERTIES CXX_CPPCHECK "${CPPCHECK_COMMAND}")
endif()

install(
    TARGETS MankalaEngine
    EXPORT MankalaEngineTargets
    PUBLIC_HEADER DESTINATION "${KDE_INSTALL_INCLUDEDIR}/mankalaengine"
    ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

install(
    EXPORT MankalaEngineTargets
    NAMESPACE MankalaEngine::
    FILE MankalaEngineConfig.cmake
    DESTINATION "${KDE_INSTALL_LIBDIR}/cmake/mankalaengine")
