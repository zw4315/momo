#include <chrono>
#include <iomanip>
#include <sstream>

#include "infrastructure/time/system_clock.h"

namespace infra::time {

std::string SystemClock::TodayYmd() const {
  using namespace std::chrono;

  // 获取当前时间点
  auto now = system_clock::now();

  // 转为 time_t（以秒为单位）
  std::time_t now_c = system_clock::to_time_t(now);

  // 转为本地时间结构体
  std::tm local_tm{};
#ifdef _WIN32
  localtime_s(&local_tm, &now_c);
#else
  localtime_r(&now_c, &local_tm);
#endif

  // 格式化为 YYYYMMDD
  std::ostringstream oss;
  oss << std::put_time(&local_tm, "%Y%m%d");
  return oss.str();
}

}  // namespace infra::time
