#include "service/calendar_service.h"
#include "utils/date_utils.h"  // 需要 DaysBetweenInclusive()

namespace {

// 将一组规则的结果合并（按位或）
Mask EvaluateAll(const DateParts& day, TagRegistry& registry,
                 const std::vector<std::shared_ptr<IMarkRule>>& rules) {
  Mask m = 0;
  for (const auto& r : rules) {
    if (r) m |= r->Evaluate(day, registry);
  }
  return m;
}

}  // namespace

CalendarViewModel CalendarService::BuildRangeCalendar(
    const std::string& start_iso, const std::string& endIso,
    const std::vector<std::shared_ptr<IMarkRule>>& extra_rules) {
  CalendarViewModel vm;

  // 1) 生成日期序列
  std::vector<DateParts> seq = DaysBetweenInclusive(start_iso, endIso);
  vm.days.reserve(seq.size());

  // 2) 规则管线：内置 Start/End + 额外规则
  std::vector<std::shared_ptr<IMarkRule>> all_rules;
  all_rules.push_back(std::make_shared<StartEndRule>(start_iso, endIso));
  all_rules.insert(all_rules.end(), extra_rules.begin(), extra_rules.end());

  // 3) 应用规则，填充 ViewModel
  for (const auto& d : seq) {
    DayCell cell;
    cell.date = d;
    cell.mask = EvaluateAll(d, registry_, all_rules);
    vm.days.push_back(cell);
  }

  return vm;
}

Mask CalendarService::ApplyRules(
    const DateParts& day, const std::string& start_iso,
    const std::string& endIso,
    const std::vector<std::shared_ptr<IMarkRule>>& extra_rules) {
  std::vector<std::shared_ptr<IMarkRule>> all_rules;
  all_rules.push_back(std::make_shared<StartEndRule>(start_iso, endIso));
  all_rules.insert(all_rules.end(), extra_rules.begin(), extra_rules.end());
  return EvaluateAll(day, registry_, all_rules);
}
