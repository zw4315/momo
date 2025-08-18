#include <sstream>

#include "presentation/views/cli/calendar_view.h"

namespace presentation {
namespace views {
namespace cli {

using app::calendar::dto::AddTagResult;
using app::calendar::dto::ViewDaysBetweenResult;

std::string CalendarViewCLI::Render(const ViewDaysBetweenResult& r) const {
  std::ostringstream os;
  os << "days=" << r.days;
  return os.str();
}

std::string CalendarViewCLI::Render(const AddTagResult& r) const {
  std::ostringstream os;
  if (r.created) {
    os << "added tag '" << r.tag << "' to " << r.dateIso;
  } else {
    os << "tag '" << r.tag << "' already exists on " << r.dateIso;
  }
  return os.str();
}

std::string CalendarViewCLI::RenderError(const std::string& msg) const {
  return std::string("error: ") + msg;
}

}  // namespace cli
}  // namespace views
}  // namespace presentation
