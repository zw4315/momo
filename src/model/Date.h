// Date.h
#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <string>

struct Date {
  int year, month, day;

  Date() : year(0), month(0), day(0) {}
  Date(int y, int m, int d) : year(y), month(m), day(d) {}

  std::string ToKey() const;                       // e.g. "20250802"
  int ToDays() const;                              // days since epoch
  static Date Gettoday();                          // current date
  static Date FromString(const std::string& str);  // e.g. "20250802"

  bool operator==(const Date& other) const;
  bool operator<(const Date& other) const;
};

int daysBetween(const Date& start, const Date& end);

#endif
