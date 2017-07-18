set(LeL_HEADERS 
  lel/operation/binary.hpp
  lel/operation/increment_decrement.hpp
  lel/operation/unary.hpp
  lel/box.hpp
  lel/context.hpp
  lel/lambda.hpp
  lel/operation.hpp
  lel/reference.hpp
  lel/variadic.hpp
  lel/wrap.hpp
  lel.hpp)

add_custom_target(LeL SOURCES ${LeL_HEADERS})

foreach(HEADER IN LISTS LeL_HEADERS)
    get_filename_component(HEADER_PATH "${HEADER}" PATH)
    string(REPLACE "/" "\\" HEADER_PATH_MSVC "${HEADER_PATH}")
    source_group("${HEADER_PATH_MSVC}" FILES "${HEADER}")
endforeach()