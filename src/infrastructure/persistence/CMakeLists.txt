# 仅内存实现（SQLite 以后再加）
add_library(momo_infra_memory
  memory/day_tags_repository_memory.cpp
)

target_include_directories(momo_infra_memory
  PUBLIC ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(momo_infra_memory
  PUBLIC momo_domain
)

# 如果将来加 sqlite 版本，另起一个库：
# add_library(momo_infra_sqlite day_tags_repository_sqlite.cpp)
# target_link_libraries(momo_infra_sqlite PUBLIC momo_domain)

