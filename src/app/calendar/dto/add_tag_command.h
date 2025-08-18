#ifndef MOMO_APPLICATION_CALENDAR_DTO_ADD_TAG_COMMAND_H_
#define MOMO_APPLICATION_CALENDAR_DTO_ADD_TAG_COMMAND_H_
#include <string>

namespace app {
namespace calendar {
namespace dto {
struct AddTagCommand {
  std::string dateIso;  // "YYYY-MM-DD"
  std::string tag;      // 非空
};
}  // namespace dto
}  // namespace calendar
}  // namespace app

#endif  // MOMO_APPLICATION_CALENDAR_DTO_ADD_TAG_COMMAND_H_
