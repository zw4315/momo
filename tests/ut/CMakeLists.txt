add_executable(unit_tests
  date_utils_test.cpp
  # test_command_registry.cpp
)

target_link_libraries(unit_tests
  utils
  gtest
  gtest_main
)

add_test(NAME AllUnitTests COMMAND unit_tests)

