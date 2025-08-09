# 源文件
set(SRC_FILES
  ./main.cpp
  ./cli/parser.cpp
  ./controller/calendar_controller.cpp
  ,/model/Date.cpp
  ./view/calendar_view.cpp
)

add_library(momo_lib ${SRC_FILES})

target_include_directories(momo_lib PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

