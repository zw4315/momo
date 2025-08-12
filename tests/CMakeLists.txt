cmake_minimum_required(VERSION 3.14)

# 依赖缓存路径（全局）
set(FETCHCONTENT_BASE_DIR "$ENV{HOME}/.cmake_deps" CACHE PATH "Base directory for FetchContent" FORCE)

find_package(GTest QUIET)
if(NOT GTest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    if(WIN32)
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    endif()
    FetchContent_MakeAvailable(googletest)
endif()

add_subdirectory(ut)

