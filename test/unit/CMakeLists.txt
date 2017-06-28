if(UNIX)
  find_package(Boost)

  if(Boost_FOUND)
    add_definitions(-DSEG_HAS_BOOST)
  endif()
endif()

include_directories(.)

add_subdirectory(seg)
