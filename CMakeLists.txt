cmake_minimum_required(VERSION 3.2)

option(BENCHMARK "Build benchmarks"         OFF)
option(COVERAGE  "Build coverage"           OFF)
option(SANITIZE  "Build with sanitizers on" OFF)
option(ENABLE_TESTING     "Build tests"              OFF)

project(LeL C CXX)

if(UNIX)
  add_compile_options(-std=c++14 -Wall -Wextra -Werror -Wpedantic)

  if(COVERAGE OR SANITIZE OR ENABLE_TESTING)
    set(CMAKE_BUILD_TYPE Debug)
    add_compile_options(-g -O0 -DDEBUG)
  else()
    set(CMAKE_BUILD_TYPE Release)
    add_compile_options(-O3 -DNDEBUG)
  endif()

  if(COVERAGE)
    add_compile_options(--coverage)
  endif()

  if(SANITIZE)
    add_compile_options(-fsanitize=address,undefined)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,undefined")
  endif()
else()
  add_compile_options(/W4 /WX)
  add_definitions(-D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING)
endif()

include_directories(include)

add_subdirectory(thirdparty)
include_directories(SYSTEM thirdparty)
include_directories(SYSTEM thirdparty/Celero/include)

if(BENCHMARK OR COVERAGE OR SANITIZE OR ENABLE_TESTING)
  enable_testing()
  add_subdirectory(test)
endif()

