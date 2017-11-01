set(lel_benchmark_SOURCES
  #increasing_number_of_arguments.cpp
  increasing_complexity.cpp
  lel_benchmark.cpp
)

add_executable(lel_benchmark ${lel_benchmark_SOURCES})
target_link_libraries(lel_benchmark celero)

target_link_libraries(lel_benchmark pthread)
