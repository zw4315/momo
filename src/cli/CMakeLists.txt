# 供业务复用与测试的库（不含 main）
add_library(timension_cli_core
    # app.cpp
    command_registry.cpp
)
# 让外部能 #include "cli/..."
target_include_directories(timension_cli_core
    PUBLIC ${PROJECT_SOURCE_DIR}/src
)
# 依赖你已有的模块库
# target_link_libraries(timension_cli_core
#     PUBLIC
#         # timension_controller
#         # timension_model
#         # timension_view_cli
#         # sqlite3
# )

# 入口可执行文件仅仅依赖 core 库
# add_executable(timension_cli
#     main.cpp
# )
# target_link_libraries(timension_cli
#     PRIVATE timension_cli_core
# )
