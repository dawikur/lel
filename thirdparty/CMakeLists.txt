include_directories(SYSTEM .)

if(TESTS OR COVERAGE)
  add_subdirectory(gtest)
endif()

if(BENCHMARK)
  set(BENCHMARK_ENABLE_TESTING OFF)
  add_subdirectory(benchmark)
endif()
