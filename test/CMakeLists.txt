
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
    -Werror
    -Wextra
    -Wpedantic
    -pedantic
  )

  if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(tests INTERFACE
      -Weverything
      -Wno-c++98-compat
      -Wno-c++98-compat-pedantic
    )
  elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(tests INTERFACE
      -Wall
      -Wcast-align
      -Wconversion
      -Wdouble-promotion
      -Wduplicated-branches
      -Wduplicated-cond
      -Wextra
      -Wformat=2
      -Wlogical-op
      -Wmisleading-indentation
      -Wnon-virtual-dtor
      -Wnull-dereference
      -Wold-style-cast
      -Woverloaded-virtual
      -Wpedantic
      -Wshadow
      -Wsign-conversion
      -Wunused
      -Wuseless-cast
      -pedantic
    )
  endif()

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
    add_definitions(-DLEL_HAS_BOOST=1)
    target_compile_definitions(tests INTERFACE LEL_HAS_BOOST=1)
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
