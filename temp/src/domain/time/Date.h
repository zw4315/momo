
#pragma once
#include <string>
#include <tuple>
#include <optional>
#include <cstdio>
#include <cstdint>

namespace momo::domain::time {

inline std::optional<std::tuple<int,int,int>> ParseDate(const std::string& s) {
  int y=0,m=0,d=0;
  if (std::sscanf(s.c_str(), "%d-%d-%d", &y, &m, &d) == 3) {
    if (m>=1 && m<=12 && d>=1 && d<=31) return {{y,m,d}};
  }
  return std::nullopt;
}

// Civil-from-days (no tz)
inline long long DaysFromCivil(int y, unsigned m, unsigned d) {
  y -= m <= 2;
  const int era = (y >= 0 ? y : y-399) / 400;
  const unsigned yoe = static_cast<unsigned>(y - era * 400);
  const unsigned doy = (153*(m + (m > 2 ? -3 : 9)) + 2)/5 + d-1;
  const unsigned doe = yoe * 365 + yoe/4 - yoe/100 + doy;
  return era * 146097LL + static_cast<long long>(doe) - 719468LL;
}

inline std::optional<long long> DaysSinceEpoch(const std::string& ymd) {
  auto p = ParseDate(ymd);
  if (!p) return std::nullopt;
  auto [y,m,d] = *p;
  return DaysFromCivil(y,(unsigned)m,(unsigned)d);
}

inline std::optional<long long> DaysBetween(const std::string& a, const std::string& b) {
  auto da = DaysSinceEpoch(a);
  auto db = DaysSinceEpoch(b);
  if (!da || !db) return std::nullopt;
  long long diff = *db - *da;
  return diff >= 0 ? diff : -diff;
}

} // namespace momo::domain::time
