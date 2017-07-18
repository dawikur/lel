include_directories(SYSTEM .)

if(TESTS OR COVERAGE)
  add_subdirectory(gtest)
endif()

if(BENCHMARK)
  add_subdirectory(benchmark)
endif()
