#ifndef SERVICE_CALENDAR_SERVICE_H_
#define SERVICE_CALENDAR_SERVICE_H_

#include <memory>
#include <string>
#include <vector>

#include "model/date_types.h"
#include "service/mark_mask.h"
#include "service/rules.h"
#include "service/tag_registry.h"

// 日历单元格
struct DayCell {
  DateParts date;
  Mask mask = 0;
};

// 日历视图模型
struct CalendarViewModel {
  std::vector<DayCell> days;
};

// 核心业务接口
class CalendarService {
 public:
  explicit CalendarService(TagRegistry& registry) : registry_(registry) {}

  // 构建日期区间日历
  CalendarViewModel BuildRangeCalendar(
      const std::string& startIso, const std::string& end_iso,
      const std::vector<std::shared_ptr<IMarkRule>>& extra_rules = {});

  TagRegistry& Tags() { return registry_; }

 private:
  TagRegistry& registry_;

  Mask ApplyRules(const DateParts& day, const std::string& startIso,
                  const std::string& end_iso,
                  const std::vector<std::shared_ptr<IMarkRule>>& extra_rules);
};

#endif  // SERVICE_CALENDAR_SERVICE_H_
