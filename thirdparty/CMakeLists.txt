
if(ENABLE_TESTING)
  add_subdirectory(gtest)
endif()

if(ENABLE_BENCHMARK)
  option(CELERO_ENABLE_EXPERIMENTS "Override Celero option" OFF)

  add_subdirectory(Celero)
endif()
