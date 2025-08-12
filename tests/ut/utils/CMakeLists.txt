file(GLOB TEST_SOURCES "test_*.cpp" "*_test.cpp")

add_executable(ut_utils_tests ${TEST_SOURCES})

target_link_libraries(ut_utils_tests
    PRIVATE
        gtest
        gtest_main
        utils
)

include(GoogleTest)
gtest_discover_tests(ut_utils_tests
    TEST_PREFIX ut.utils.
    DISCOVERY_MODE PRE_TEST
    PROPERTIES LABELS "ut;utils"
)


