add_library(timension_model
    event.cpp
    storage.cpp
)

target_include_directories(timension_model PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(timension_model sqlite3)

