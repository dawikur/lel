set(seg_test_SOURCES
  double_placeholders.cpp
  meta.cpp
  nested_single_placeholder.cpp
  single_placeholder.cpp
)

add_executable(seg_test ${seg_test_SOURCES})
target_link_libraries(seg_test gtest)

if(UNIX)
  target_link_libraries(seg_test pthread gcov)
endif()

add_test(seg seg_test --gtest_color=yes)
