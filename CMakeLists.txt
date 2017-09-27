cmake_minimum_required(VERSION 3.2)

option(TESTS     "Build tests"      OFF)
option(COVERAGE  "Build coverage"   OFF)
option(BENCHMARK "Build benchmarks" OFF)

project(LeL C CXX)

if(UNIX)
  add_compile_options(-std=c++14 -Wall -Wextra -Werror -Wpedantic)
  if(COVERAGE OR TESTS)
    set(CMAKE_BUILD_TYPE Debug)
    add_compile_options(-g -O0 -DDEBUG)
  else()
    set(CMAKE_BUILD_TYPE Release)
    add_compile_options(-O3 -DNDEBUG)
  endif()
else()
  add_compile_options(/W4 /WX)
endif()

add_subdirectory(include)

if(TESTS OR COVERAGE OR BENCHMARK)
  enable_testing()

  add_subdirectory(thirdparty)

  include_directories(SYSTEM thirdparty)
  include_directories(include)

  add_subdirectory(test)
endif()
