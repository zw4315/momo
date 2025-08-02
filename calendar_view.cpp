// calendar_view.cpp
#include <iomanip>
#include <iostream>
#include <sstream>

#include "calendar_view.h"

static const int BOX_WIDTH = 22;
static const int BOX_HEIGHT = 8;

static int getDaysInMonth(int year, int month) {
  static const int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  if (month != 2) return days[month - 1];
  return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 29 : 28;
}

static int getWeekday(int year, int month, int day) {
  if (month < 3) {
    month += 12;
    --year;
  }
  int h =
      (day + 13 * (month + 1) / 5 + year + year / 4 - year / 100 + year / 400) %
      7;
  return (h + 6) % 7;  // Sunday = 0
}

static std::string getMonthName(int month) {
  static const char* names[] = {
      "January", "February", "March",     "April",   "May",      "June",
      "July",    "August",   "September", "October", "November", "December"};
  return names[month - 1];
}

// 生成单个月份的 8 行表示：1 行标题，1 行 weekday header，最多 6 行数字
static std::vector<std::string> generateMonthBlock(int year, int month) {
  std::vector<std::string> lines;

  std::ostringstream title;
  title << std::setw(BOX_WIDTH) << std::right
        << getMonthName(month) + " " + std::to_string(year);
  lines.push_back(title.str());
  lines.push_back("Su Mo Tu We Th Fr Sa");

  int startWeekday = getWeekday(year, month, 1);
  int days = getDaysInMonth(year, month);

  std::ostringstream line;
  int day = 1, wd = 0;
  for (int i = 0; i < startWeekday; ++i) {
    line << "   ";
    ++wd;
  }

  while (day <= days) {
    line << std::setw(2) << day << " ";
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

void printCalendarRange(int startYear, int startMonth, int endYear,
                        int endMonth) {
  std::vector<std::vector<std::string>> months;

  for (int y = startYear; y <= endYear; ++y) {
    int m1 = (y == startYear) ? startMonth : 1;
    int m2 = (y == endYear) ? endMonth : 12;
    for (int m = m1; m <= m2; ++m) {
      months.push_back(generateMonthBlock(y, m));
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
}
