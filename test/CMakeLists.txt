include(ECMAddTests)
file(GLOB_RECURSE TEST_FILES Test*.cpp)
ecm_add_tests(${TEST_FILES}
    LINK_LIBRARIES MankalaEngine Qt6::Test
    TARGET_NAMES_VAR TEST_TARGETS)
set_target_properties(${TEST_TARGETS} PROPERTIES AUTOMOC ON)
