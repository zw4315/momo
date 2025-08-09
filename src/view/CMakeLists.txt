add_library(timension_view_cli
    cli/renderer.cpp
)

target_include_directories(timension_view_cli PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(timension_view_cli timension_model)

