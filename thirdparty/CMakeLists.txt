
add_library(thirdparty INTERFACE)

target_include_directories(thirdparty SYSTEM INTERFACE .)
target_link_libraries(thirdparty INTERFACE settings)

if(ENABLE_TESTING)
  add_subdirectory(gtest)
endif()

if(ENABLE_BENCHMARK)
  option(CELERO_ENABLE_EXPERIMENTS "Override Celero option" OFF)

  add_subdirectory(Celero)

  target_include_directories(thirdparty SYSTEM INTERFACE Celero/include)
endif()
