#include <gtest/gtest.h>

#include <regex>

#include "utils/date_utils.h"

// 检查返回值格式是否正确（YYYYMMDD）
TEST(DateUtilsTest, ReturnsCorrectFormat) {
  std::string dateStr = timension::utils::GetTodayDateStr();

  // 用正则匹配 8 位数字
  std::regex pattern(R"(^\d{8}$)");
  EXPECT_TRUE(std::regex_match(dateStr, pattern))
      << "Date string format is incorrect: " << dateStr;
}

// 检查返回的日期是否是今天
TEST(DateUtilsTest, ReturnsTodayDate) {
  std::string expected = timension::utils::GetTodayDateStr();

  // 获取系统当前时间
  std::time_t t = std::time(nullptr);
  std::tm tm_local{};
#ifdef _WIN32
  localtime_s(&tm_local, &t);
#else
  localtime_r(&t, &tm_local);
#endif
  char buffer[9];
  std::strftime(buffer, sizeof(buffer), "%Y%m%d", &tm_local);
  std::string systemToday(buffer);

  EXPECT_EQ(expected, systemToday)
      << "Expected " << systemToday << " but got " << expected;
}
