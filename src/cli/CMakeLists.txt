add_executable(timension_cli
    main.cpp
    app.cpp
    command_registry.cpp
)

target_include_directories(timension_cli PRIVATE
    ${PROJECT_SOURCE_DIR}/src/controller
    ${PROJECT_SOURCE_DIR}/src/model
    ${PROJECT_SOURCE_DIR}/src/view
)

target_link_libraries(timension_cli
    timension_controller
    timension_model
    timension_view_cli
    sqlite3
)

