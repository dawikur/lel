set(lel_benchmark_SOURCES
  increasing_complexity_of_expressions.cpp
  increasing_number_of_arguments.cpp
  lel_benchmark.cpp
  simple_expression_in_loop.cpp
)

add_executable(lel_benchmark ${lel_benchmark_SOURCES})
target_link_libraries(lel_benchmark benchmark)

if(UNIX)
  target_link_libraries(lel_benchmark pthread)
endif()
