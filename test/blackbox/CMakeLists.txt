set(blackbox_test_SOURCES
  0_sizeof_lambdas.cpp
  1_single_std_placeholder.cpp
  2_single_lel_placeholder.cpp
  3_double_std_placeholders.cpp
  4_double_lel_placeholders.cpp
  5_nested_single_std_placeholder.cpp
  6_nested_single_lel_placeholder.cpp
  7_nested_double_std_placeholder.cpp
  8_nested_double_lel_placeholder.cpp
  9_curring.cpp
)

add_executable(blackbox_test ${blackbox_test_SOURCES})
target_link_libraries(blackbox_test gtest)

if(UNIX)
  target_link_libraries(blackbox_test pthread gcov)
endif()

add_test(blackbox blackbox_test --gtest_color=yes)
