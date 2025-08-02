cmake_minimum_required(VERSION 3.10)
project(CalendarCLI)

# 使用 C++11（或你可以选择 17/20）
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含所有源文件
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/cli/parser.cpp
    ${SRC_DIR}/controller/calendar_controller.cpp
    ${SRC_DIR}/model/Date.cpp
    ${SRC_DIR}/view/calendar_view.cpp
)

# 添加可执行文件
add_executable(calendar ${SOURCES})

# 包含头文件搜索路径
target_include_directories(calendar PRIVATE
    ${SRC_DIR}
    ${SRC_DIR}/cli
    ${SRC_DIR}/controller
    ${SRC_DIR}/model
    ${SRC_DIR}/view
)

