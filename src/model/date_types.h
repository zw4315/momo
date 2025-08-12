#ifndef MODEL_DATE_TYPES_H_
#define MODEL_DATE_TYPES_H_

#include <string>

struct DateParts {
  int year = 0;
  int month = 0;
  int day = 0;
  int weekday = 0;  // 0 = Sunday, 1 = Monday, ...
  std::string iso;  // "YYYY-MM-DD"
};

#endif  // MODEL_DATE_TYPES_H_
