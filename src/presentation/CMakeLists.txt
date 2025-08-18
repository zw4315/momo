# 展示层：控制器 + CLI 视图
add_library(momo_presentation
  controllers/calendar_controller.cpp
  views/cli/calendar_view.cpp
)

target_include_directories(momo_presentation
  PUBLIC ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(momo_presentation
  PUBLIC momo_application_calendar
)

