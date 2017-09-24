set(lel_test_SOURCES
  box.cpp
  context.cpp
  functors.cpp
  lambda.cpp
  operation.cpp
  reference.cpp
  tuple.cpp
  variadic.cpp
  wrap.cpp
)

add_executable(lel_test ${lel_test_SOURCES})
target_link_libraries(lel_test gtest)

if(UNIX)
  target_link_libraries(lel_test pthread gcov)
endif()

add_test(lel lel_test --gtest_color=yes)

add_subdirectory(operation)
