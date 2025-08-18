// tests/ut/app/test_calendar_service.cpp
#include <gtest/gtest.h>

#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "app/calendar/dto/view_days_between_dto.h"
#include "app/calendar/ports/calendar_use_case.h"
#include "app/calendar/ports/day_tag_repository.h"
#include "app/calendar/use_cases/calendar_service.h"

// 一个简单的内存仓储假实现，用于 UT
class FakeDayTagRepository : public app::calendar::ports::IDayTagRepository {
 public:
  bool ExistsTag(const std::string& date_iso, const std::string& tag) override {
    auto it = store_.find(date_iso);
    if (it == store_.end()) return false;
    return it->second.count(tag) > 0;
  }

  void AddTag(const std::string& date_iso, const std::string& tag) override {
    store_[date_iso].insert(tag);
  }

  std::vector<std::string> ListTags(const std::string& date_iso) override {
    std::vector<std::string> out;
    auto it = store_.find(date_iso);
    if (it == store_.end()) return out;
    out.assign(it->second.begin(), it->second.end());
    return out;
  }

  // test-only helper
  bool Has(const std::string& date_iso, const std::string& tag) const {
    auto it = store_.find(date_iso);
    if (it == store_.end()) return false;
    return it->second.count(tag) > 0;
  }

 private:
  std::unordered_map<std::string, std::unordered_set<std::string>> store_;
};

using app::calendar::ports::ICalendarUseCase;
using app::calendar::usecases::CalendarService;
namespace dto = app::calendar::dto;

// ---------- ViewDaysBetween ----------

TEST(CalendarService_ViewDaysBetween, BasicOneDay) {
  FakeDayTagRepository repo;
  CalendarService svc(repo);

  dto::ViewDaysBetweenQuery q{"2025-05-01", "2025-05-02"};
  auto r = svc.ViewDaysBetween(q);
  EXPECT_EQ(r.days, 1);
}

TEST(CalendarService_ViewDaysBetween, SameDayIsZero) {
  FakeDayTagRepository repo;
  CalendarService svc(repo);

  dto::ViewDaysBetweenQuery q{"2025-05-01", "2025-05-01"};
  auto r = svc.ViewDaysBetween(q);
  EXPECT_EQ(r.days, 0);
}

TEST(CalendarService_ViewDaysBetween, MultipleDays) {
  FakeDayTagRepository repo;
  CalendarService svc(repo);

  dto::ViewDaysBetweenQuery q{"2025-05-01", "2025-05-12"};
  auto r = svc.ViewDaysBetween(q);
  EXPECT_EQ(r.days, 11);
}

TEST(CalendarService_ViewDaysBetween, LeapYear29FebIncluded) {
  FakeDayTagRepository repo;
  CalendarService svc(repo);

  dto::ViewDaysBetweenQuery q{"2024-02-27", "2024-03-01"};
  auto r = svc.ViewDaysBetween(q);
  EXPECT_EQ(r.days, 3);  // 27->28, 28->29, 29->Mar1
}

TEST(CalendarService_ViewDaysBetween, FromAfterToThrows) {
  FakeDayTagRepository repo;
  CalendarService svc(repo);

  dto::ViewDaysBetweenQuery q{"2025-05-02", "2025-05-01"};
  EXPECT_THROW(svc.ViewDaysBetween(q), std::invalid_argument);
}

TEST(CalendarService_ViewDaysBetween, InvalidDateFormatThrows) {
  FakeDayTagRepository repo;
  CalendarService svc(repo);

  dto::ViewDaysBetweenQuery q{"2025-13-40", "2025-05-01"};
  EXPECT_THROW(svc.ViewDaysBetween(q), std::invalid_argument);
}

// ---------- AddTagToDay ----------

TEST(CalendarService_AddTagToDay, AddNewTagReturnsCreatedTrue) {
  FakeDayTagRepository repo;
  CalendarService svc(repo);

  dto::AddTagCommand cmd{"2025-05-01", "work"};
  auto r = svc.AddTagToDay(cmd);

  EXPECT_TRUE(r.created);
  EXPECT_EQ(r.date_iso, "2025-05-01");
  EXPECT_EQ(r.tag, "work");
  EXPECT_TRUE(repo.Has("2025-05-01", "work"));
}

TEST(CalendarService_AddTagToDay, IdempotentSecondCallReturnsFalse) {
  FakeDayTagRepository repo;
  CalendarService svc(repo);

  dto::AddTagCommand cmd{"2025-05-01", "work"};
  auto r1 = svc.AddTagToDay(cmd);
  auto r2 = svc.AddTagToDay(cmd);

  EXPECT_TRUE(r1.created);
  EXPECT_FALSE(r2.created);
}

TEST(CalendarService_AddTagToDay, MultipleTagsOnSameDay) {
  FakeDayTagRepository repo;
  CalendarService svc(repo);

  auto r1 = svc.AddTagToDay({"2025-05-01", "work"});
  auto r2 = svc.AddTagToDay({"2025-05-01", "gym"});

  EXPECT_TRUE(r1.created);
  EXPECT_TRUE(r2.created);
  EXPECT_TRUE(repo.Has("2025-05-01", "work"));
  EXPECT_TRUE(repo.Has("2025-05-01", "gym"));
}

TEST(CalendarService_AddTagToDay, InvalidDateThrows) {
  FakeDayTagRepository repo;
  CalendarService svc(repo);

  dto::AddTagCommand cmd{"2025-13-01", "x"};
  EXPECT_THROW(svc.AddTagToDay(cmd), std::invalid_argument);
}

TEST(CalendarService_AddTagToDay, EmptyTagThrows) {
  FakeDayTagRepository repo;
  CalendarService svc(repo);

  dto::AddTagCommand cmd{"2025-05-01", ""};
  EXPECT_THROW(svc.AddTagToDay(cmd), std::invalid_argument);
}
