add_executable(lel_test
  context.cpp
  functor.cpp
  lambda.cpp
  operator/binary.cpp
  operator/increment_decrement.cpp
  operator/unary.cpp
  reference.cpp
  template/box.cpp
  template/sequence.cpp
  template/variadic.cpp
  wrap.cpp
)
target_link_libraries(lel_test tests)
target_include_directories(lel_test PRIVATE .)

add_test(lel lel_test --gtest_color=yes)
