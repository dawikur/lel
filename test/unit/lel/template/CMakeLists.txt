set(lel_template_test_SOURCES
  box.cpp
  variadic.cpp
)

add_executable(lel_template_test ${lel_template_test_SOURCES})
target_link_libraries(lel_template_test gtest)

if(UNIX)
  target_link_libraries(lel_template_test pthread gcov)
endif()

add_test(lel_template lel_template_test --gtest_color=yes)
