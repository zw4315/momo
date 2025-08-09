add_library(timension_controller
    controller.cpp
)

target_include_directories(timension_controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(timension_controller timension_model)

