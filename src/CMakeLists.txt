set(
    HEADER_LIST
    "../include/mankalaengine/mankalaengine.h"
    "../include/mankalaengine/rules.h"
    "../include/mankalaengine/bohnenspielrules.h"
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
    $<INSTALL_INTERFACE:include/mankalaengine>)

target_compile_features(MankalaEngine PUBLIC cxx_std_11)
set_target_properties(MankalaEngine PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(MankalaEngine PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(MankalaEngine PROPERTIES PUBLIC_HEADER "${PUBLIC_HEADER_LIST}")

if(CLANG_TIDY_COMMAND)
    set_target_properties(MankalaEngine PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
endif()
if(CPPCHECK_COMMAND)
    set_target_properties(MankalaEngine PROPERTIES CXX_CPPCHECK "${CPPCHECK_COMMAND}")
endif()

install(
    TARGETS MankalaEngine
    EXPORT MankalaEngineTargets
    PUBLIC_HEADER DESTINATION include/mankalaengine
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)

install(
    EXPORT MankalaEngineTargets
    NAMESPACE MankalaEngine::
    FILE MankalaEngineConfig.cmake
    DESTINATION lib/cmake/mankalaengine)
