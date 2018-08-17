add_executable(lel_operation_test
  binary.cpp
  increment_decrement.cpp
  unary.cpp
)
target_link_libraries(lel_operation_test testing)

add_test(lel_operation lel_operation_test --gtest_color=yes)
