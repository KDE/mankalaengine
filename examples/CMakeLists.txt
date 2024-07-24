file(GLOB_RECURSE EXAMPLES *.cpp)
if(BUILD_EXAMPLES)
    foreach(example_src ${EXAMPLES})
        get_filename_component(example_name ${example_src} NAME_WE)

        add_executable(${example_name} ${example_src})
        target_link_libraries(${example_name} PRIVATE MankalaEngine)

        target_include_directories(${example_name} PUBLIC ../include/mankalaengine)

        target_compile_features(${example_name} PUBLIC cxx_std_11)
        set_target_properties(${example_name} PROPERTIES CXX_EXTENSIONS OFF)
        set_target_properties(${example_name} PROPERTIES CXX_STANDARD_REQUIRED ON)
    endforeach()
endif()
