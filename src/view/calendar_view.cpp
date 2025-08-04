// calendar_view.cpp
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "calendar_controller.h"
#include "calendar_view.h"

static const int BOX_WIDTH = 22;
static const int BOX_HEIGHT = 8;

static std::string HighlightDay(int day, const std::string& type) {
  std::ostringstream out;
  if (type == "start") {
    out << "\033[103m" << std::setw(2) << day << "\033[0m";  // 亮黄底
  } else if (type == "end") {
    out << "\033[101m" << std::setw(2) << day << "\033[0m";  // 亮红底
  } else if (type == "today") {
    out << "\033[107;30m" << std::setw(2) << day << "\033[0m";  // 白底黑字
  } else {
    out << std::setw(2) << day;
  }
  return out.str();
}

static int GetDaysInMonth(int year, int month) {
  static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (month != 2) return days[month - 1];
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
}

static int GetWeekday(int year, int month, int day) {
  if (month < 3) {
    month += 12;
    --year;
  }
  int h =
      (day + 13 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) %
      7;
  return (h + 6) % 7;  // Sunday = 0
}

static std::string GetMonthName(int month) {
  static const char* names[] = {
      "January", "February", "March",     "April",   "May",      "June",
      "July",    "August",   "September", "October", "November", "December"};
  return names[month - 1];
}

static std::vector<std::string> GenerateMonthBlock(
    int year, int month, const std::map<std::string, std::string>& highlights) {
  std::vector<std::string> lines;
  std::ostringstream title;
  title << std::setw(BOX_WIDTH) << std::right
        << GetMonthName(month) + " " + std::to_string(year);
  lines.push_back(title.str());
  lines.push_back("Su Mo Tu We Th Fr Sa");

  int startWeekday = GetWeekday(year, month, 1);
  int days = GetDaysInMonth(year, month);

  std::ostringstream line;
  int day = 1, wd = 0;
  for (int i = 0; i < startWeekday; ++i) {
    line << "   ";
    ++wd;
  }

  while (day <= days) {
    std::ostringstream dateKey;
    dateKey << std::setw(4) << std::setfill('0') << year << std::setw(2)
            << std::setfill('0') << month << std::setw(2) << std::setfill('0')
            << day;

    std::string type = "normal";
    auto it = highlights.find(dateKey.str());
    if (it != highlights.end()) {
      type = it->second;
    }
    line << HighlightDay(day, type) << " ";
    ++day;
    ++wd;
    if (wd == 7) {
      lines.push_back(line.str());
      line.str("");
      line.clear();
      wd = 0;
    }
  }
  if (wd != 0) {
    while (wd++ < 7) line << "   ";
    lines.push_back(line.str());
  }
  while (lines.size() < BOX_HEIGHT) {
    lines.push_back("");
  }
  return lines;
}

void PrintCalendarRange(const CalendarContext& ctx) {
  std::vector<std::vector<std::string>> months;

  int startY = ctx.startDate.year;
  int startM = ctx.startDate.month;
  int endY = ctx.endDate.year;
  int endM = ctx.endDate.month;

  for (int y = startY; y <= endY; ++y) {
    int m1 = (y == startY) ? startM : 1;
    int m2 = (y == endY) ? endM : 12;
    for (int m = m1; m <= m2; ++m) {
      months.push_back(GenerateMonthBlock(y, m, ctx.highlightMap));
    }
  }

  const int blocksPerRow = 3;
  for (size_t i = 0; i < months.size(); i += blocksPerRow) {
    size_t rowCount = std::min((size_t)blocksPerRow, months.size() - i);
    for (int line = 0; line < BOX_HEIGHT; ++line) {
      for (size_t j = 0; j < rowCount; ++j) {
        std::cout << std::left << std::setw(BOX_WIDTH) << months[i + j][line];
      }
      std::cout << "\n";
    }
    std::cout << "\n";
  }

  std::cout << "\n" << ctx.summaryMessage << "\n";
}
