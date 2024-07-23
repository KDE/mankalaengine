file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${MankalaEngine_SOURCE_DIR}/include/mankala-engine/*\.(h|hpp)")

add_library(mankalaengine mankalaengine.cpp rules.cpp bohnenspielrules.cpp moveselection.cpp ${HEADER_LIST})

target_include_directories(mankalaengine PUBLIC ../include/mankalaengine)

target_compile_features(mankalaengine PUBLIC cxx_std_11)
set_target_properties(mankalaengine PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(mankalaengine PROPERTIES CXX_STANDARD_REQUIRED ON)
if(CLANG_TIDY_COMMAND)
  set_target_properties(mankalaengine PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")
endif()
if(CPPCHECK_COMMAND)
  set_target_properties(mankalaengine PROPERTIES CXX_CPPCHECK "${CPPCHECK_COMMAND}")
endif()
