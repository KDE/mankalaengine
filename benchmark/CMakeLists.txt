add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark PRIVATE MankalaEngine)

target_include_directories(benchmark PUBLIC ../include/mankalaengine)
ecm_mark_nongui_executable(benchmark)
