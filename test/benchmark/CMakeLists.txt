set(seg_benchmark_SOURCES
  seg_benchmark.cpp
)

add_executable(seg_benchmark ${seg_benchmark_SOURCES})
target_link_libraries(seg_benchmark benchmark)

if(UNIX)
  target_link_libraries(seg_benchmark pthread)
endif()
