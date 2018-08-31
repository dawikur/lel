add_library(gtest STATIC
  gtest-all.cc
  gtest_main.cc
)
target_include_directories(gtest SYSTEM PUBLIC ../)
