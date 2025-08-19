add_library(momo_infra_time
  system_clock.cpp
)

target_include_directories(momo_infra_time
  PUBLIC ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(momo_infra_time
  PUBLIC momo_domain
)

