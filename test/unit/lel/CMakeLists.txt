add_executable(lel_test
  context.cpp
  functor.cpp
  lambda.cpp
  reference.cpp
  wrap.cpp
)
target_link_libraries(lel_test testing)

add_test(lel lel_test --gtest_color=yes)

add_subdirectory(operation)
add_subdirectory(template)
