file(GLOB_RECURSE TEST_FILES Test*.cpp)
foreach(test_src ${TEST_FILES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_compile_features(${test_name} PRIVATE cxx_std_11)
    target_link_libraries(${test_name} PRIVATE MankalaEngine Qt6::Test)

    if (WIN32)
        add_custom_command(
            TARGET ${test_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E
            copy_if_different
            $<TARGET_RUNTIME_DLLS:${test_name}> $<TARGET_FILE_DIR:${test_name}>
            COMMAND_EXPAND_LISTS)
    endif ()
    add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
