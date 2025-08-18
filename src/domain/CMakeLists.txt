# 领域层：目前只有 rules.cpp 有实现文件，其他是 header-only
add_library(momo_domain
  tags/rules.cpp
)

target_include_directories(momo_domain
  PUBLIC ${CMAKE_SOURCE_DIR}/src
)

# 如你把 date.* 或 date_range_service.* 改为 .cpp 实现，记得加进来：
# target_sources(momo_domain PRIVATE calendar/date.cpp calendar/date_range_service.cpp)

