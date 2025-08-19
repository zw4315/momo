#ifndef MOMO_DOMAIN_TAGS_DAY_TAGS_H_
#define MOMO_DOMAIN_TAGS_DAY_TAGS_H_

#include <string>
#include <unordered_set>
#include <vector>

#include "domain/calendar/date.h"

namespace domain {
namespace tags {

// 聚合：某一“日”的标签集合。
// 领域内处理幂等（AddTag 已存在则返回 false），删除返回是否真的删到。
class DayTags {
 public:
  explicit DayTags(const domain::calendar::Date& day) : day_(day) {}

  const domain::calendar::Date& date() const { return day_; }

  bool HasTag(const std::string& tag) const {
    return tags_.find(tag) != tags_.end();
  }

  // 返回 true 表示真的新增；false 表示已存在（幂等）
  bool AddTag(const std::string& tag) {
    if (tag.empty()) return false;  // 也可抛异常，按你的口径决定
    auto [it, inserted] = tags_.insert(tag);
    return inserted;
  }

  bool RemoveTag(const std::string& tag) { return tags_.erase(tag) > 0; }

  std::vector<std::string> List() const {
    std::vector<std::string> out;
    out.reserve(tags_.size());
    for (const auto& t : tags_) out.push_back(t);
    return out;
  }

  std::size_t size() const { return tags_.size(); }

 private:
  domain::calendar::Date day_;
  std::unordered_set<std::string> tags_;
};

}  // namespace tags
}  // namespace domain

#endif  // MOMO_DOMAIN_TAGS_DAY_TAGS_H_
