set(lel_sanitize_SOURCES
  sanitize.cpp
)

add_executable(lel_sanitize ${lel_sanitize_SOURCES})

target_link_libraries(lel_sanitize pthread)
