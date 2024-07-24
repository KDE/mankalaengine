add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark PRIVATE MankalaEngine)

target_include_directories(benchmark PUBLIC ../include/mankalaengine)

target_compile_features(benchmark PUBLIC cxx_std_11)
set_target_properties(benchmark PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(benchmark PROPERTIES CXX_STANDARD_REQUIRED ON)
