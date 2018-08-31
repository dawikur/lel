
add_library(tests INTERFACE)

target_link_libraries(tests INTERFACE
  gtest
  lel
)

if(MSVC)
  target_compile_options(tests INTERFACE /W4 /WX)
else()
  target_compile_options(tests INTERFACE
    -Wall
    -Wextra
    -Werror
    -Wpedantic
  )

  if(ENABLE_COVERAGE)
    target_compile_options(tests INTERFACE
      --coverage
    )

    target_link_libraries(tests INTERFACE
      gcov
    )
  endif()


  target_link_libraries(tests INTERFACE
    pthread
  )

  find_package(Boost)

  if(Boost_FOUND)
    target_compile_definitions(tests INTERFACE -DLEL_HAS_BOOST)
  endif()
endif()

if(ENABLE_BENCHMARK)
  add_subdirectory(benchmark)
endif()

if(ENABLE_COVERAGE)
  add_subdirectory(unit)
endif()

if(ENABLE_TESTING)
  add_subdirectory(blackbox)
  add_subdirectory(sanitize)
  add_subdirectory(unit)
endif()
