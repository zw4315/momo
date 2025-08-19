# CLI 组合根（库，不含 main）
add_library(momo_cli_lib
  cli_shell.cpp
  command_registry.cpp
)

target_include_directories(momo_cli_lib
  PUBLIC ${CMAKE_SOURCE_DIR}/src
)

# CLI 需要把所有下层库连起来（应用、展示、基础设施）
target_link_libraries(momo_cli_lib
  PUBLIC
    momo_presentation
    momo_application_calendar
    momo_infra_memory
    momo_infra_time
    momo_domain
)

