file(GLOB TEST_SOURCES "test_*.cpp" "*_test.cpp")

add_executable(ut_cli_tests ${TEST_SOURCES})

target_link_libraries(ut_cli_tests
    PRIVATE
        gtest
        gtest_main
        utils
        timension_cli_core
    )

include(GoogleTest)
gtest_discover_tests(ut_cli_tests
    TEST_PREFIX ut.cli.
    DISCOVERY_MODE PRE_TEST
    PROPERTIES LABELS "ut;cli"
)


