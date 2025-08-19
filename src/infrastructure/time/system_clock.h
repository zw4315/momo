#ifndef INFRASTRUCTURE_TIME_SYSTEM_CLOCK_H_
#define INFRASTRUCTURE_TIME_SYSTEM_CLOCK_H_

#include <string>

#include "domain/common/ports/clock.h"

namespace infra::time {

class SystemClock : public domain::common::ports::Clock {
 public:
  ~SystemClock() override = default;

  std::string TodayYmd() const override;
};

}  // namespace infra::time

#endif  // INFRASTRUCTURE_TIME_SYSTEM_CLOCK_H_
