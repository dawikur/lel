if(UNIX)
  find_package(Boost)

  if(Boost_FOUND)
    add_definitions(-DLEL_HAS_BOOST)
  endif()
endif()

if(TESTS)
  add_subdirectory(blackbox)
  add_subdirectory(unit)
endif()

if(COVERAGE)
  add_subdirectory(unit)
endif()

if(BENCHMARK)
  add_subdirectory(benchmark)
endif()
