# CLI 可执行程序入口（只有 main.cpp）
add_executable(momo_cli
  main.cpp
)

target_link_libraries(momo_cli
  PRIVATE
    momo_cli_lib
)

# 方便 #include "..." 从 src/ 根开始
target_include_directories(momo_cli
  PRIVATE ${CMAKE_SOURCE_DIR}/src
)

