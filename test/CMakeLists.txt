
add_library(testing INTERFACE)

target_link_libraries(testing INTERFACE
  gtest
  lel
  settings
  thirdparty
)

if(UNIX)
  find_package(Boost)

  if(Boost_FOUND)
    target_compile_definitions(testing INTERFACE -DLEL_HAS_BOOST)
  endif()
endif()

if(ENABLE_BENCHMARK)
  add_subdirectory(benchmark)
endif()

if(ENABLE_TESTING)
  add_subdirectory(blackbox)
  add_subdirectory(sanitize)
  add_subdirectory(unit)
endif()
