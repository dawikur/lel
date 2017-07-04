// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel_benchmark.hpp"

#include <algorithm>
#include <vector>

#include <cstdlib>

#ifdef LEL_HAS_BOOST

#include <boost/tuple/tuple.hpp>
#include <boost/lambda/lambda.hpp>

void simple_expression__bll(::benchmark::State &state) {
  using namespace boost::lambda;

  auto const expression = _1 * _2;

  std::vector<int> vec(100);
  std::generate(vec.begin(), vec.end(), std::rand);

  while (state.KeepRunning()) {
    for (int i = 0; i <= state.range(0); ++i) {
      std::transform(vec.begin(), vec.end(), vec.begin(), expression);
    }
  }
}
BENCHMARK(simple_expression__bll)->Range(0, 20);

#endif  // LEL_HAS_BOOST

void simple_expression__lel(::benchmark::State &state) {
  using namespace LeL::Placeholders;

  auto const expression = _x * _x;

  std::vector<int> vec(100);
  std::generate(vec.begin(), vec.end(), std::rand);

  while (state.KeepRunning()) {
    for (int i = 0; i <= state.range(0); ++i) {
      std::transform(vec.begin(), vec.end(), vec.begin(), expression);
    }
  }
}
BENCHMARK(simple_expression__lel)->Range(0, 20);

void simple_expression__lambda(::benchmark::State &state) {
  auto const expression = [](auto _x) { return _x * _x; };

  std::vector<int> vec(100);
  std::generate(vec.begin(), vec.end(), std::rand);

  while (state.KeepRunning()) {
    for (int i = 0; i <= state.range(0); ++i) {
      std::transform(vec.begin(), vec.end(), vec.begin(), expression);
    }
  }
}
BENCHMARK(simple_expression__lambda)->Range(0, 20);
