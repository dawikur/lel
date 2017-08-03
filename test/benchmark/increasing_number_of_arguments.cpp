// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel_benchmark.hpp"

#include <cstdlib>

#include <algorithm>
#include <vector>

template <class Expression, class... Args>
void histogram__increasing_number_of_arguments(::benchmark::State const &state,
                                               Expression const expression,
                                               Args... args) {
  std::vector<double> vec(10);
  std::generate(vec.begin(), vec.end(), std::rand);

  while (state.KeepRunning()) {
    for (int i = 0; i < 1000; ++i) {
      benchmark::DoNotOptimize(expression(vec[args]...));
    }
  }
}

auto const a = 3;
auto const b = 7;

auto const lA = LeL::Placeholders::_a;
auto const lB = LeL::Placeholders::_b;
auto const lC = LeL::Placeholders::_c;
auto const lD = LeL::Placeholders::_d;
auto const lE = LeL::Placeholders::_e;
auto const lF = LeL::Placeholders::_f;

BENCHMARK_CAPTURE(histogram__increasing_number_of_arguments, LeL/1,
                  ((a * lA - (a + lA)) * (b * lA - (b + lA)) * (a * lA - (b + lA)) * (b * lA - (a + lA))),
                  4);
BENCHMARK_CAPTURE(histogram__increasing_number_of_arguments, LeL/2,
                  ((a * lA - (a + lB)) * (b * lA - (b + lB)) * (a * lA - (b + lA)) * (b * lA - (a + lA))),
                  4, 7);
BENCHMARK_CAPTURE(histogram__increasing_number_of_arguments, LeL/3,
                  ((a * lA - (a + lB)) * (b * lA - (b + lB)) * (a * lA - (b + lC)) * (b * lA - (a + lC))),
                  4, 7, 9);
BENCHMARK_CAPTURE(histogram__increasing_number_of_arguments, LeL/4,
                  ((a * lD - (a + lB)) * (b * lA - (b + lB)) * (a * lA - (b + lC)) * (b * lA - (a + lC))),
                  4, 7, 9, 2);
BENCHMARK_CAPTURE(histogram__increasing_number_of_arguments, LeL/5,
                  ((a * lD - (a + lB)) * (b * lE - (b + lB)) * (a * lA - (b + lC)) * (b * lA - (a + lC))),
                  4, 7, 9, 2, 8);
BENCHMARK_CAPTURE(histogram__increasing_number_of_arguments, LeL/6,
                  ((a * lD - (a + lB)) * (b * lE - (b + lB)) * (a * lF - (b + lC)) * (b * lA - (a + lC))),
                  4, 7, 9, 2, 8, 15);

BENCHMARK_CAPTURE(histogram__increasing_number_of_arguments, Lambda/1,
                  [](auto A) { return (a * A - (a + A)) * (b * A - (b + A)) * (a * A - (b + A)) * (b * A - (a + A)); },
                  4);
BENCHMARK_CAPTURE(histogram__increasing_number_of_arguments, Lambda/2,
                  [](auto A, auto B) { return (a * A - (a + B)) * (b * A - (b + B)) * (a * A - (b + A)) * (b * A - (a + A)); },
                  4, 7);
BENCHMARK_CAPTURE(histogram__increasing_number_of_arguments, Lambda/3,
                  [](auto A, auto B, auto C) { return (a * A - (a + B)) * (b * A - (b + B)) * (a * A - (b + C)) * (b * A - (a + C)); },
                  4, 7, 9);
BENCHMARK_CAPTURE(histogram__increasing_number_of_arguments, Lambda/4,
                  [](auto A, auto B, auto C, auto D) { return (a * D - (a + B)) * (b * A - (b + B)) * (a * A - (b + C)) * (b * A - (a + C)); },
                  4, 7, 9, 2);
BENCHMARK_CAPTURE(histogram__increasing_number_of_arguments, Lambda/5,
                  [](auto A, auto B, auto C, auto D, auto E) { return (a * D - (a + B)) * (b * E - (b + B)) * (a * A - (b + C)) * (b * A - (a + C)); },
                  4, 7, 9, 2, 8);
BENCHMARK_CAPTURE(histogram__increasing_number_of_arguments, Lambda/6,
                  [](auto A, auto B, auto C, auto D, auto E, auto F) { return (a * D - (a + B)) * (b * E - (b + B)) * (a * F - (b + C)) * (b * A - (a + C)); },
                  4, 7, 9, 2, 8, 15);

#ifdef LEL_HAS_BOOST

#include <boost/lambda/lambda.hpp>

auto const bA = boost::lambda::_1;
auto const bB = boost::lambda::_2;
auto const bC = boost::lambda::_3;

BENCHMARK_CAPTURE(histogram__increasing_number_of_arguments, BLL/1,
                  (a * bA - (a + bA)) * (b * bA - (b + bA)) * (a * bA - (b + bA)) * (b * bA - (a + bA)),
                  4);
BENCHMARK_CAPTURE(histogram__increasing_number_of_arguments, BLL/2,
                  (a * bA - (a + bB)) * (b * bA - (b + bB)) * (a * bA - (b + bA)) * (b * bA - (a + bA)),
                  4, 7);
BENCHMARK_CAPTURE(histogram__increasing_number_of_arguments, BLL/3,
                  (a * bA - (a + bB)) * (b * bA - (b + bB)) * (a * bA - (b + bC)) * (b * bA - (a + bC)),
                  4, 7, 9);

#endif  // LEL_HAS_BOOST
