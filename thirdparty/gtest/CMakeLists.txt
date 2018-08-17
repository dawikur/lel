set(gtest_SOURCES
  gtest-all.cc
  gtest_main.cc
)

add_library(gtest STATIC ${gtest_SOURCES})
target_link_libraries(gtest thirdparty)
