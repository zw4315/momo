# src/app/cli/CMakeLists.txt

add_executable(momo_cli main.cpp)

target_link_libraries(momo_cli
    PRIVATE momo_presentation_cli
    PRIVATE momo_infra_time
    PRIVATE momo_infra_memory
    PRIVATE momo_application_calendar
)

# 方便 #include "..." 从 src/ 根开始
target_include_directories(momo_cli
  PRIVATE ${CMAKE_SOURCE_DIR}/src
)

