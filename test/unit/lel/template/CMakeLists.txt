add_executable(lel_template_test
  box.cpp
  sequence.cpp
  variadic.cpp
)
target_link_libraries(lel_template_test testing)

add_test(lel_template lel_template_test --gtest_color=yes)
