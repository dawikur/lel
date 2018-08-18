add_executable(lel_test
  context.cpp
  functor.cpp
  lambda.cpp
  operation/binary.cpp
  operation/increment_decrement.cpp
  operation/unary.cpp
  reference.cpp
  template/box.cpp
  template/sequence.cpp
  template/variadic.cpp
  wrap.cpp
)
target_link_libraries(lel_test testing)
target_include_directories(lel_test PRIVATE .)

add_test(lel lel_test --gtest_color=yes)
