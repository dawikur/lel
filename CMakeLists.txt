cmake_minimum_required(VERSION 3.8)

option(ENABLE_BENCHMARK "Build benchmarks"     OFF)
option(ENABLE_TESTING   "Build tests"          OFF)
option(ENABLE_COVERAGE  "Build coverage tests" OFF)

project(LeL C CXX)

add_library(lel INTERFACE)

target_include_directories(lel INTERFACE include)
target_compile_features(lel INTERFACE
  cxx_std_14
)

if(ENABLE_BENCHMARK OR ENABLE_COVERAG OR ENABLE_TESTING)
  enable_testing()

  add_subdirectory(thirdparty)
  add_subdirectory(test)
endif()

