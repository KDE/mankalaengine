include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

include(GoogleTest)
file(GLOB_RECURSE TEST_FILES *_test.cpp)
if(BUILD_TESTING)
    SET(CMAKE_CXX_FLAGS "-g -O0 --coverage")
    foreach(test_src ${TEST_FILES})
        get_filename_component(test_name ${test_src} NAME_WE)
        add_executable(${test_name} ${test_src})
        target_compile_features(${test_name} PRIVATE cxx_std_17)
        target_link_libraries(${test_name} PRIVATE mankalaengine GTest::GTest)
        gtest_discover_tests(${test_name})
    endforeach()
endif()
