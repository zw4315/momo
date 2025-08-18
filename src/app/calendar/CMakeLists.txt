# 应用层：日历用例（use_cases）
add_library(momo_application_calendar
  use_cases/calendar_service.cpp
)

target_include_directories(momo_application_calendar
  PUBLIC ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(momo_application_calendar
  PUBLIC momo_domain
)

