add_executable(sanitize_test
  sanitize.cpp
)
target_link_libraries(sanitize_test testing)

add_test(sanitize sanitize_test --gtest_color=yes)
