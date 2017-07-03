if(UNIX)
  find_package(Boost)

  if(Boost_FOUND)
    add_definitions(-DLEL_HAS_BOOST)
  endif()
endif()

include_directories(.)

add_subdirectory(lel)
