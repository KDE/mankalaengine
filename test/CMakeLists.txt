include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)

file(GLOB_RECURSE TEST_FILES *_test.cpp)
if(BUILD_TESTING)
    foreach(test_src ${TEST_FILES})
        get_filename_component(test_name ${test_src} NAME_WE)
        add_executable(${test_name} ${test_src})
        target_compile_features(${test_name} PRIVATE cxx_std_11)
        target_link_libraries(${test_name} PRIVATE mankalaengine Catch2::Catch2WithMain)
        catch_discover_tests(${test_name})
    endforeach()
endif()
