#ifndef DOMAIN_COMMON_PORTS_CLOCK_H_
#define DOMAIN_COMMON_PORTS_CLOCK_H_

#include <string>

namespace domain::common::ports {

class Clock {
 public:
  virtual ~Clock() = default;

  // 返回今天的日期，格式为 YYYYMMDD
  virtual std::string TodayYmd() const = 0;
};

}  // namespace domain::common::ports

#endif  // DOMAIN_COMMON_PORTS_CLOCK_H_
