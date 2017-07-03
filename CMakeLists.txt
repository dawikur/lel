cmake_minimum_required(VERSION 2.8.0)

option(TESTS     "Build also tests"      OFF)
option(COVERAGE  "Build for coverage"    OFF)
option(BENCHMARK "Build also benchmarks" OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(LeL C CXX)

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Werror -Wpedantic")
  if(COVERAGE OR TESTS)
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
  else()
    set(CMAKE_BUILD_TYPE Release)
  endif()
else()
  set(warnings "/W4 /WX")
endif()

if(TESTS OR COVERAGE OR BENCHMARK)
  enable_testing()

  add_subdirectory(thirdparty)

  include_directories(SYSTEM thirdparty)
  include_directories(include)

  add_subdirectory(test)
endif()
