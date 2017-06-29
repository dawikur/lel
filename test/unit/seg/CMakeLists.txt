set(seg_test_SOURCES
  impl.cpp
  operation.cpp
  utility.cpp
)

add_executable(seg_test ${seg_test_SOURCES})
target_link_libraries(seg_test gtest)

if(UNIX)
  target_link_libraries(seg_test pthread gcov)
endif()

add_test(seg seg_test --gtest_color=yes)
