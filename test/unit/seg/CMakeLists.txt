set(seg_test_SOURCES
  box.cpp
  context.cpp
  impl.cpp
  operation.cpp
  variadic.cpp
)

add_executable(seg_test ${seg_test_SOURCES})
target_link_libraries(seg_test gtest)

if(UNIX)
  target_link_libraries(seg_test pthread gcov)
endif()

add_test(seg seg_test --gtest_color=yes)
