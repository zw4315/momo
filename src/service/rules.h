#ifndef SERVICE_RULES_H_
#define SERVICE_RULES_H_

#include <string>

#include "model/date_types.h"
#include "service/mark_mask.h"
#include "service/tag_registry.h"

// 打标签规则接口
class IMarkRule {
 public:
  virtual ~IMarkRule() = default;

  // 针对某一天返回标签掩码
  virtual Mask Evaluate(const DateParts& day, TagRegistry& registry) = 0;
};

// 起止高亮规则
class StartEndRule : public IMarkRule {
 public:
  StartEndRule(const std::string& startIso, const std::string& endIso)
      : start_iso_(startIso), end_iso_(endIso) {}

  Mask Evaluate(const DateParts& day, TagRegistry& registry) override;

 private:
  std::string start_iso_;
  std::string end_iso_;
};

#endif  // SERVICE_RULES_H_
