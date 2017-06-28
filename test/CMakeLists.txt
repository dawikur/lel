if(TESTS)
  add_subdirectory(unit)
endif()

if(COVERAGE)
  add_subdirectory(unit)
endif()

if(BENCHMARK)
  add_subdirectory(benchmark)
endif()
