set(lel_operation_test_SOURCES
  binary.cpp
  increment_decrement.cpp
  unary.cpp
)

add_executable(lel_operation_test ${lel_operation_test_SOURCES})
target_link_libraries(lel_operation_test gtest)

if(UNIX)
  target_link_libraries(lel_operation_test pthread gcov)
endif()

add_test(lel_operation lel_operation_test --gtest_color=yes)
