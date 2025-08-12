# 自动收集本目录下所有 UT 源文件
file(GLOB TEST_SOURCES "test_*.cpp" "*_test.cpp")

add_executable(ut_service_tests ${TEST_SOURCES})

target_link_libraries(ut_service_tests
  PRIVATE
    gmock
    gtest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(ut_service_tests
    TEST_PREFIX ut.service.
    DISCOVERY_MODE PRE_TEST
    PROPERTIES LABELS "ut;service"
)
