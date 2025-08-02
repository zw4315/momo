// Date.cpp
#include <cmath>
#include <iomanip>
#include <sstream>
#include <tuple>

#include "Date.h"

Date Date::fromString(const std::string& str) {
  if (str.length() != 8) throw std::invalid_argument("Invalid date format");
  return Date{std::stoi(str.substr(0, 4)), std::stoi(str.substr(4, 2)),
              std::stoi(str.substr(6, 2))};
}

std::string Date::toKey() const {
  std::ostringstream oss;
  oss << std::setw(4) << std::setfill('0') << year << std::setw(2)
      << std::setfill('0') << month << std::setw(2) << std::setfill('0') << day;
  return oss.str();
}

int Date::toDays() const {
  std::tm tm_date = {};
  tm_date.tm_year = year - 1900;
  tm_date.tm_mon = month - 1;
  tm_date.tm_mday = day;
  tm_date.tm_hour = 0;
  tm_date.tm_min = 0;
  tm_date.tm_sec = 0;
  std::time_t time = std::mktime(&tm_date);
  return static_cast<int>(time / 86400);  // convert seconds to days
}

Date Date::today() {
  std::time_t t = std::time(nullptr);
  std::tm* now = std::localtime(&t);
  return Date(now->tm_year + 1900, now->tm_mon + 1, now->tm_mday);
}

bool Date::operator==(const Date& other) const {
  return year == other.year && month == other.month && day == other.day;
}

bool Date::operator<(const Date& other) const {
  return std::tie(year, month, day) <
         std::tie(other.year, other.month, other.day);
}

int daysBetween(const Date& start, const Date& end) {
  return std::abs(end.toDays() - start.toDays());
}
