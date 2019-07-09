add_executable(sanitize_test
  sanitize.cpp
)
target_link_libraries(sanitize_test tests)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  target_compile_options(sanitize_test PRIVATE
  )
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  target_compile_options(sanitize_test PRIVATE
  )
endif()

add_test(sanitize sanitize_test --gtest_color=yes)
