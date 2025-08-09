#include <ctime>
#include <iomanip>
#include <sstream>

#include "utils/date_utils.h"

namespace timension {
namespace utils {

std::string GetTodayDateStr() {
  std::time_t t = std::time(nullptr);
  std::tm tm_local{};
#ifdef _WIN32
  localtime_s(&tm_local, &t);
#else
  localtime_r(&t, &tm_local);
#endif
  char buffer[9];
  std::strftime(buffer, sizeof(buffer), "%Y%m%d", &tm_local);
  return std::string(buffer);
}

}  // namespace utils
}  // namespace timension
