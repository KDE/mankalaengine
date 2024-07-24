set(
    HEADER_LIST
    "../include/mankalaengine/mankalaengine.h"
    "../include/mankalaengine/rules.h"
    "../include/mankalaengine/bohnenspielrules.h"
    "../include/mankalaengine/moveselection.h"
    "../include/mankalaengine/variantdescriptions.h")

add_library(
    MankalaEngine
    mankalaengine.cpp
    rules.cpp
    bohnenspielrules.cpp
    moveselection.cpp
    ${HEADER_LIST})

target_include_directories(
    MankalaEngine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include/mankalaengine>
    $<INSTALL_INTERFACE:include/mankalaengine>)

target_compile_features(MankalaEngine PUBLIC cxx_std_11)
set_target_properties(MankalaEngine PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(MankalaEngine PROPERTIES CXX_STANDARD_REQUIRED ON)
set_target_properties(MankalaEngine PROPERTIES PUBLIC_HEADER "${HEADER_LIST}")

if(CLANG_TIDY_COMMAND AND NOT WIN32)
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
