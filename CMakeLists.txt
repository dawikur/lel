cmake_minimum_required(VERSION 3.5.1)

option(TESTS     "Build tests"      OFF)
option(COVERAGE  "Build coverage"   OFF)
option(BENCHMARK "Build benchmarks" OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(LeL C CXX)

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Werror -Wpedantic")
  if(COVERAGE OR TESTS)
    set(CMAKE_BUILD_TYPE Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -DDEBUG")
  else()
    set(CMAKE_BUILD_TYPE Release)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG")
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
