cmake_minimum_required(VERSION 3.16)
project(timension)

# ---- C++ STANDARD  ----
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- SOURCE MODULE ----
add_subdirectory(src/utils)
# add_subdirectory(src/model)
# add_subdirectory(src/controller)
# add_subdirectory(src/view)
# add_subdirectory(src/cli)

include(CTest)             # 只负责开启/关闭测试开关 BUILD_TESTING
if(BUILD_TESTING)
  add_subdirectory(tests)  # 测试细节都在 tests/ 里处理
endif()






