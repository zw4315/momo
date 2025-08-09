#include <gtest/gtest.h>

#include "cli/command_registry.h"

using namespace timension::cli;

TEST(CommandRegistryTest, DispatchKnownCommand) {
  CommandRegistry& registry = CommandRegistry::GetInstance();

  bool called = false;
  registry.Register(
      "testcmd",
      [&](const std::vector<std::string>& args) {
        called = true;
        EXPECT_EQ(args.size(), 2);  // 注册的时候，会跳过前两个，只注册真正 args
        EXPECT_EQ(args[0], "foo");
        EXPECT_EQ(args[1], "bar");
        return 0;
      },
      "Test command");

  const char* argv[] = {"timension", "testcmd", "foo", "bar"};
  int result = registry.Dispatch(4, argv);
  EXPECT_EQ(result, 0);
  EXPECT_TRUE(called);
}
