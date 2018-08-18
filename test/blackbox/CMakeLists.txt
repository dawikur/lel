add_executable(blackbox_test
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
  10_constexpr.cpp
  11_function_call.cpp
  12_pointer_to_member.cpp
)
target_link_libraries(blackbox_test testing)

add_test(blackbox blackbox_test --gtest_color=yes)
