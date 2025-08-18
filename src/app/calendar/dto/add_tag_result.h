#ifndef MOMO_APPLICATION_CALENDAR_DTO_ADD_TAG_RESULT_H_
#define MOMO_APPLICATION_CALENDAR_DTO_ADD_TAG_RESULT_H_
#include <string>

namespace app {
namespace calendar {
namespace dto {
struct AddTagResult {
  std::string dateIso;
  std::string tag;
  bool created;  // true=新增，false=已存在（幂等）
};
}  // namespace dto
}  // namespace calendar
}  // namespace app
#endif  // MOMO_APPLICATION_CALENDAR_DTO_ADD_TAG_RESULT_H_
