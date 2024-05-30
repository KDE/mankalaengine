file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${MankalaEngine_SOURCE_DIR}/include/mankala-engine/*\.(h|hpp)")

add_library(mankalaengine mankalaengine.cpp bohnenspielrules.cpp ${HEADER_LIST})

target_include_directories(mankalaengine PUBLIC ../include/mankalaengine)

target_compile_features(mankalaengine PUBLIC cxx_std_17)
set_target_properties(mankalaengine PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(mankalaengine PROPERTIES CXX_STANDARD_REQUIRED ON)
