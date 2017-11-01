include_directories(SYSTEM .)

if(TESTS OR COVERAGE)
  add_subdirectory(gtest)
endif()

if(BENCHMARK)
  set(CELERO_ENABLE_EXPERIMENTS OFF)
  add_subdirectory(Celero)
endif()
