#ifndef MOMO_DOMAIN_CALENDAR_DATE_H_
#define MOMO_DOMAIN_CALENDAR_DATE_H_

#include <cctype>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <tuple>

namespace domain {
namespace calendar {

// 值对象：不可变日期（公历），支持 "YYYYMMDD"（推荐）与 "YYYY-MM-DD"（兼容）。
class Date {
 public:
  // 构造并校验范围
  Date(int year, int month, int day) : y_(year), m_(month), d_(day) {
    Validate();
  }

  // === 首选：8 位紧凑格式 ===
  // 从 "YYYYMMDD" 解析（非法抛 std::invalid_argument）
  static Date FromYmd8(const std::string& ymd8) {
    if (ymd8.size() != 8) {
      throw std::invalid_argument("Date::FromYmd8: invalid length");
    }
    for (char c : ymd8) {
      if (!std::isdigit(static_cast<unsigned char>(c))) {
        throw std::invalid_argument("Date::FromYmd8: non-digit");
      }
    }
    int year = (ymd8[0] - '0') * 1000 + (ymd8[1] - '0') * 100 +
               (ymd8[2] - '0') * 10 + (ymd8[3] - '0');
    int month = (ymd8[4] - '0') * 10 + (ymd8[5] - '0');
    int day = (ymd8[6] - '0') * 10 + (ymd8[7] - '0');
    return Date(year, month, day);
  }

  // 转为 "YYYYMMDD"
  std::string ToYmd8() const {
    char buf[9];  // "YYYYMMDD"
    std::snprintf(buf, sizeof(buf), "%04d%02d%02d", y_, m_, d_);
    return std::string(buf);
  }

  // === 兼容：ISO 带横杠格式 ===
  static Date FromIso(const std::string& iso) {
    if (iso.size() != 10 || iso[4] != '-' || iso[7] != '-') {
      throw std::invalid_argument("Date::FromIso: invalid format");
    }
    auto is_digit3 = [](char c) {
      return std::isdigit(static_cast<unsigned char>(c)) != 0;
    };
    for (int i : {0, 1, 2, 3, 5, 6, 8, 9}) {
      if (!is_digit3(iso[static_cast<size_t>(i)])) {
        throw std::invalid_argument("Date::FromIso: non-digit");
      }
    }
    int year = (iso[0] - '0') * 1000 + (iso[1] - '0') * 100 +
               (iso[2] - '0') * 10 + (iso[3] - '0');
    int month = (iso[5] - '0') * 10 + (iso[6] - '0');
    int day = (iso[8] - '0') * 10 + (iso[9] - '0');
    return Date(year, month, day);
  }

  std::string ToIso() const {
    char buf[11];  // "YYYY-MM-DD"
    std::snprintf(buf, sizeof(buf), "%04d-%02d-%02d", y_, m_, d_);
    return std::string(buf);
  }

  // === 过渡期辅助：自动识别两种输入格式 ===
  // 优先尝试 8 位；若不符合且像 "YYYY-MM-DD"，则走 ISO。
  static Date FromString(const std::string& s) {
    if (s.size() == 8) return FromYmd8(s);
    if (s.size() == 10 && s[4] == '-' && s[7] == '-') return FromIso(s);
    throw std::invalid_argument("Date::FromString: unsupported date format");
  }

  // 访问器
  int year() const { return y_; }
  int month() const { return m_; }
  int day() const { return d_; }

  // 比较：按 (y,m,d)
  bool operator==(const Date& o) const {
    return y_ == o.y_ && m_ == o.m_ && d_ == o.d_;
  }
  bool operator<(const Date& o) const {
    return std::tie(y_, m_, d_) < std::tie(o.y_, o.m_, o.d_);
  }
  bool operator<=(const Date& o) const { return !(o < *this); }

 private:
  static bool IsLeap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
  }
  static int DaysInMonth(int y, int m) {
    if (m < 1 || m > 12) return 0;
    static const int kDays[13] = {0,  31, 28, 31, 30, 31, 30,
                                  31, 31, 30, 31, 30, 31};
    return (m == 2) ? kDays[m] + (IsLeap(y) ? 1 : 0) : kDays[m];
  }
  void Validate() const {
    if (m_ < 1 || m_ > 12)
      throw std::invalid_argument("Date: month out of range");
    int dim = DaysInMonth(y_, m_);
    if (d_ < 1 || d_ > dim)
      throw std::invalid_argument("Date: day out of range");
  }

 private:
  int y_;
  int m_;
  int d_;
};

}  // namespace calendar
}  // namespace domain

#endif  // MOMO_DOMAIN_CALENDAR_DATE_H_
