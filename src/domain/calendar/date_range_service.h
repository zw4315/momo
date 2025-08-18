#ifndef MOMO_DOMAIN_CALENDAR_DATE_RANGE_SERVICE_H_
#define MOMO_DOMAIN_CALENDAR_DATE_RANGE_SERVICE_H_
/* 计算自然日之差 */

#include <climits>
#include <cstdint>

#include "domain/calendar/date.h"

namespace domain {
namespace calendar {

// 计算两个公历日期之间相差的自然天数（跨越的午夜次数）。
// 约定：返回 b - a；即 2025-05-01 到 2025-05-02 为 1；同日为 0。
// 若 b < a，结果为负数；通常由应用层在进入此函数前保证 from <= to。
struct DateRangeService {
  // 将日期映射为一个单调递增的“序列日”计数（整数）。
  // 算法来源于经典的 civil 日历整数映射（类似 Howard Hinnant 的
  // days_from_civil）， 仅用整数运算，正确处理闰年与世纪规则：
  //   闰年 = (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0)
  static inline std::int64_t ToSerialDays(const Date& d) {
    int y = d.year();
    int m = d.month();
    int day = d.day();

    // 将一年视为从 3 月开始，Jan/Feb 归入上一年，便于闰年修正
    y -= (m <= 2 ? 1 : 0);

    // 400 年一个 era，共 146097 天（含 97 个闰年）
    const int era = (y >= 0 ? y : y - 399) / 400;               // floor(y/400)
    const unsigned yoe = static_cast<unsigned>(y - era * 400);  // [0,399]

    // 将月映射到从 3 月开始的序号：Mar=0,...,Jan=10,Feb=11
    const unsigned mp = static_cast<unsigned>(m + (m > 2 ? -3 : 9));  // [0,11]

    // 当年内的日序（0-based），使用 153*mp+2 的整式避免分支
    const unsigned doy =
        (153u * mp + 2u) / 5u + static_cast<unsigned>(day) - 1u;  // [0,365]

    // era 内的日序（0-based）：平年 365，加上闰年修正 yoe/4 - yoe/100
    const unsigned doe =
        yoe * 365u + yoe / 4u - yoe / 100u + doy;  // [0,146096]

    // 返回自某个固定原点起的绝对日序；原点具体值不重要（仅用于差值）
    return static_cast<std::int64_t>(era) * 146097 +
           static_cast<std::int64_t>(doe);
  }

  // 返回 b 与 a 的自然日差：b 的序列日 - a 的序列日
  static inline int DaysBetween(const Date& a, const Date& b) {
    const std::int64_t da = ToSerialDays(a);
    const std::int64_t db = ToSerialDays(b);
    const std::int64_t diff = db - da;

    // 正常业务范围内不会溢出 int，这里做一次防御性裁剪
    if (diff > static_cast<std::int64_t>(INT_MAX)) return INT_MAX;
    if (diff < static_cast<std::int64_t>(INT_MIN)) return INT_MIN;
    return static_cast<int>(diff);
  }
};

}  // namespace calendar
}  // namespace domain

#endif  // MOMO_DOMAIN_CALENDAR_DATE_RANGE_SERVICE_H_
