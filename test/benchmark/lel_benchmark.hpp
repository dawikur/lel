// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef TEST_BENCHMARK_LEL_BENCHMARK_HPP_
#define TEST_BENCHMARK_LEL_BENCHMARK_HPP_

#include <cstdlib>

#include <algorithm>
#include <vector>

#include "lel.hpp"

#include "celero/Celero.h"

#ifdef LEL_HAS_BOOST

#include <boost/lambda/lambda.hpp>

#endif  // LEL_HAS_BOOST

#define TEST(                                                                  \
  TYPE, ARGUMENTS, VARIABLES, NAME, PRE, POST, A, B, C, D, E, F, ...)          \
  TYPE(Benchmark_##ARGUMENTS##_##VARIABLES, NAME, 1000, 1000) {                \
    for (int i = 0; i < 13; ++i)                                               \
      celero::DoNotOptimizeAway(PRE((5 * D - (5 + B)) * (7 * E - (7 + B))      \
                                    * (5 * F - (7 + C)) * (7 * A - (5 + C)))   \
                                  POST(__VA_ARGS__));                          \
  }

#endif  // TEST_BENCHMARK_LEL_BENCHMARK_HPP_
