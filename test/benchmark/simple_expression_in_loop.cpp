// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel_benchmark.hpp"

#include <algorithm>
#include <vector>

#include <cstdlib>

template <class Expression>
void simple_expression_in_loop(::benchmark::State &state,
                               Expression const    expression) {
  std::vector<int> vec(100);
  std::generate(vec.begin(), vec.end(), std::rand);

  while (state.KeepRunning()) {
    for (int i = 0; i <= state.range(0); ++i) {
      std::transform(vec.begin(), vec.end(), vec.begin(), expression);
    }
  }
}

auto eLeL    = LeL::Placeholders::_x * LeL::Placeholders::_x + 3;
auto eLambda = [](auto const _x) { return _x * _x + 3; };

BENCHMARK_CAPTURE(simple_expression_in_loop, LeL, eLeL)->Range(0, 100);
BENCHMARK_CAPTURE(simple_expression_in_loop, Lambda, eLambda)->Range(0, 100);

#ifdef LEL_HAS_BOOST

#include <boost/lambda/lambda.hpp>

auto eBLL   = boost::lambda::_1 * boost::lambda::_1 + 3;

BENCHMARK_CAPTURE(simple_expression_in_loop, BLL, eBLL)->Range(0, 100);

#endif  // LEL_HAS_BOOST
