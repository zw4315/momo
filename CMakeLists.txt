cmake_minimum_required(VERSION 3.10)
project(CalendarCLI)

# 使用 C++11 或更高标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 源文件
set(SOURCES
    main.cpp
    parser.cpp
    calendar_view.cpp
)

# 生成可执行文件
add_executable(calendar ${SOURCES})

# 如果有头文件放在 include/ 目录，将来可添加：
# target_include_directories(calendar PRIVATE include)

