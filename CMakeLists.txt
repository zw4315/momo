cmake_minimum_required(VERSION 3.10)
project(momo)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置源目录
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# 源文件
set(SOURCES
  ${SRC_DIR}/main.cpp
  ${SRC_DIR}/cli/parser.cpp
  ${SRC_DIR}/controller/calendar_controller.cpp
  ${SRC_DIR}/model/Date.cpp
  ${SRC_DIR}/view/calendar_view.cpp
)

# 添加可执行文件，改名为 momo
add_executable(momo ${SOURCES})

# 头文件搜索路径
target_include_directories(momo PRIVATE
  ${SRC_DIR}
  ${SRC_DIR}/cli
  ${SRC_DIR}/controller
  ${SRC_DIR}/model
  ${SRC_DIR}/view
)

# 安装规则
install(TARGETS momo RUNTIME DESTINATION bin)

