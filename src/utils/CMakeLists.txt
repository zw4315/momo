# 构建 utils 库（目前只有 date_utils）
add_library(utils
    date_utils.cpp
)

target_include_directories(utils
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/..  # 让外部 include 从 src 开始
)

