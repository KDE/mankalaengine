include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
    EXCLUDE_FROM_ALL
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

include(GoogleTest)
file(GLOB_RECURSE TEST_FILES *_test.cpp)
foreach(test_src ${TEST_FILES})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_compile_features(${test_name} PRIVATE cxx_std_11)
    target_link_libraries(${test_name} PRIVATE MankalaEngine GTest::GTest)

    if (WIN32)
        add_custom_command(
            TARGET ${test_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E
            copy_if_different
            $<TARGET_RUNTIME_DLLS:${test_name}> $<TARGET_FILE_DIR:${test_name}>
            COMMAND_EXPAND_LISTS)
    endif ()

    gtest_discover_tests(${test_name})
endforeach()
