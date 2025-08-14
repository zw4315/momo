
# Domain
add_library(momo_domain
  domain/tags/Tag.h
  domain/tags/TagRegistry.cpp
  domain/tags/TagRegistry.h
  domain/tags/ports/ITagRepository.h
  domain/time/Date.h
  domain/calendar/DayTagRegistry.cpp
  domain/calendar/DayTagRegistry.h
)
target_include_directories(momo_domain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Application
add_library(momo_application
  application/tags/TagService.cpp
  application/tags/TagService.h
  application/tags/ports/ITagUseCase.h
)
target_link_libraries(momo_application PUBLIC momo_domain)
target_include_directories(momo_application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Infrastructure (file + optional sqlite)
add_library(momo_infrastructure
  infrastructure/persistence/file/FileTagRepository.cpp
  infrastructure/persistence/file/FileTagRepository.h
)
# Try find SQLite3
find_package(SQLite3 QUIET)
if (SQLite3_FOUND)
  target_sources(momo_infrastructure PRIVATE
    infrastructure/persistence/sqlite/SqliteTagRepository.cpp
    infrastructure/persistence/sqlite/SqliteTagRepository.h
  )
  target_link_libraries(momo_infrastructure PUBLIC momo_domain PRIVATE SQLite::SQLite3)
  add_compile_definitions(MOMO_HAVE_SQLITE=1)
else()
  message(STATUS "SQLite3 not found: building without sqlite adapter")
  target_link_libraries(momo_infrastructure PUBLIC momo_domain)
endif()
target_include_directories(momo_infrastructure PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Presentation
add_library(momo_presentation
  presentation/mvc/controllers/TagsController.cpp
)
target_link_libraries(momo_presentation PUBLIC momo_application)
target_include_directories(momo_presentation PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Boot
add_library(momo_boot
  boot/CompositionRoot.cpp
  boot/CompositionRoot.h
  boot/Warmup.h
)
target_link_libraries(momo_boot PUBLIC momo_domain momo_application momo_infrastructure)
target_include_directories(momo_boot PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# CLI
add_executable(momo_cli cli/main.cpp)
target_link_libraries(momo_cli PRIVATE momo_boot momo_presentation)
