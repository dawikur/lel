set(blackbox_test_SOURCES
  double_placeholders.cpp
  meta.cpp
  nested_single_placeholder.cpp
  single_placeholder.cpp
)

add_executable(blackbox_test ${blackbox_test_SOURCES})
target_link_libraries(blackbox_test gtest)

if(UNIX)
  target_link_libraries(blackbox_test pthread gcov)
endif()

add_test(blackbox blackbox_test --gtest_color=yes)
