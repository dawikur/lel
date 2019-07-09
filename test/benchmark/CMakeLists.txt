add_executable(benchmark_test
  lel_benchmark.cpp
)
target_link_libraries(benchmark_test celero)
target_link_libraries(benchmark_test lel)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  target_compile_options(benchmark_test PRIVATE
  )
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  target_compile_options(benchmark_test PRIVATE
  )
endif()
