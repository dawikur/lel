include_directories(SYSTEM .)

if(ENABLE_TESTING OR COVERAGE)
  add_subdirectory(gtest)
endif()

if(BENCHMARK)
  option(CELERO_ENABLE_EXPERIMENTS "Override Celero option" OFF)

  add_subdirectory(Celero)
endif()
