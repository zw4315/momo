# presentation/cli/CMakeLists.txt

# 收集源文件
set(CLI_SOURCES
    cli_shell.cpp
    commands/command_registry.cpp
    controllers/calendar_controller.cpp
    views/calendar_view.cpp
)

set(CLI_HEADERS
    cli_shell.h
    commands/command_registry.h
    controllers/calendar_controller.h
    views/calendar_view.h
)

add_library(momo_presentation_cli ${CLI_SOURCES} ${CLI_HEADERS})

# 依赖 app 层（调用 use case）
target_link_libraries(momo_presentation_cli
    PRIVATE
    momo_application_calendar
    momo_infra_memory
    momo_infra_time
    momo_domain
)

