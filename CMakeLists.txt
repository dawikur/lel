cmake_minimum_required(VERSION 3.8)

option(ENABLE_BENCHMARK "Build benchmarks" OFF)
option(ENABLE_TESTING   "Build tests"      OFF)

project(LeL C CXX)

add_library(settings INTERFACE)

if(MSVC)
  target_compile_options(settings INTERFACE /W4 /WX)
else()
  target_compile_options(settings INTERFACE
    -Wall
    -Wextra
    -Werror
    -Wpedantic

    --coverage
  )

  target_compile_features(settings INTERFACE
    cxx_std_14
  )

  target_link_libraries(settings INTERFACE
    gcov
    pthread
  )
endif()

add_library(lel INTERFACE)

target_include_directories(lel INTERFACE include)
target_link_libraries(lel INTERFACE settings)

add_subdirectory(thirdparty)

if(ENABLE_BENCHMARK OR ENABLE_TESTING)
  enable_testing()

  add_subdirectory(test)
endif()

