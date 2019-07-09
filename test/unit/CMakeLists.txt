add_executable(unit_test
  context.cpp
  lambda.cpp
  operator.cpp
  operator/binary.cpp
  operator/increment_decrement.cpp
  operator/unary.cpp
  rebind.cpp
  reference.cpp
  template/box.cpp
  template/sequence.cpp
  template/variadic.cpp
  wrap.cpp
)
target_link_libraries(unit_test tests)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  target_compile_options(unit_test PRIVATE
    -Wno-exit-time-destructors
    -Wno-global-constructors
    -Wno-padded
    -Wno-weak-vtables
  )
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  target_compile_options(unit_test PRIVATE
  )
endif()

target_include_directories(unit_test PRIVATE .)

add_test(unit unit_test --gtest_color=yes)
