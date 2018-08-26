add_executable(lel_benchmark
  lel_benchmark.cpp
)
target_link_libraries(lel_benchmark celero)
target_link_libraries(lel_benchmark lel)
