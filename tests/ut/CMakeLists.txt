add_executable(unit_tests
  date_utils_test.cpp
  test_command_registry.cpp
)

target_link_libraries(unit_tests
  PRIVATE
    gtest gtest_main
    timension_cli_core
    utils
)

include(GoogleTest)
gtest_discover_tests(unit_tests
  TEST_PREFIX unit.           # 可选：给名字加前缀
  DISCOVERY_MODE PRE_TEST     # 运行前动态发现
  TEST_LIST UT_LIST
)

# 打标签，便于筛选
set_tests_properties(${UT_LIST} PROPERTIES LABELS "ut")

