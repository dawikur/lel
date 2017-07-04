// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel_benchmark.hpp"

#include <algorithm>
#include <vector>

#include <cstdlib>

template <class Expression>
void increasing_complexity_of_expressions(::benchmark::State &state,
                                          Expression const    expression) {
  std::vector<double> vec(100);
  std::generate(vec.begin(), vec.end(), std::rand);

  while (state.KeepRunning()) {
    std::transform(vec.begin(), vec.end(), vec.begin(), expression);
  }
}

auto const a = 3;
auto const b = 7;

auto const lX = LeL::Placeholders::_x;

BENCHMARK_CAPTURE(increasing_complexity_of_expressions, LeL/1, a * lX);
BENCHMARK_CAPTURE(increasing_complexity_of_expressions, LeL/2, -a * lX);
BENCHMARK_CAPTURE(increasing_complexity_of_expressions, LeL/3, a * lX - (a + lX));
BENCHMARK_CAPTURE(increasing_complexity_of_expressions, LeL/4, (a * lX - (a + lX)) * (a + lX));
BENCHMARK_CAPTURE(increasing_complexity_of_expressions, LeL/5, (a * lX - (a + lX)) * (b * lX - (b + lX)) * (a * lX - (b + lX)) * (b * lX - (a + lX)));

BENCHMARK_CAPTURE(increasing_complexity_of_expressions, Lambda/5, [] (auto x) { return a*x; });
BENCHMARK_CAPTURE(increasing_complexity_of_expressions, Lambda/5, [] (auto x) { return -a*x; });
BENCHMARK_CAPTURE(increasing_complexity_of_expressions, Lambda/5, [] (auto x) { return a*x-(a+x); });
BENCHMARK_CAPTURE(increasing_complexity_of_expressions, Lambda/5, [] (auto x) { return (a*x - (a+x))*(a+x); });
BENCHMARK_CAPTURE(increasing_complexity_of_expressions, Lambda/5, [] (auto x) { return (a*x - (a+x))*(b*x - (b+x))*(a*x - (b+x))*(b*x - (a+x)); });

#ifdef LEL_HAS_BOOST

#include <boost/lambda/lambda.hpp>

auto const bX = boost::lambda::_1;

BENCHMARK_CAPTURE(increasing_complexity_of_expressions, BLL/1, a * bX);
BENCHMARK_CAPTURE(increasing_complexity_of_expressions, BLL/2, -a * bX);
BENCHMARK_CAPTURE(increasing_complexity_of_expressions, BLL/3, a * bX - (a + bX));
BENCHMARK_CAPTURE(increasing_complexity_of_expressions, BLL/4, (a * bX - (a + bX)) * (a + bX));
BENCHMARK_CAPTURE(increasing_complexity_of_expressions, BLL/5, (a * bX - (a + bX)) * (b * bX - (b + bX)) * (a * bX - (b + bX)) * (b * bX - (a + bX)));

#endif  // LEL_HAS_BOOST
