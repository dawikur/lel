// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel_benchmark.hpp"

#include <cstdlib>

#include <algorithm>
#include <vector>

struct Fixture : celero::TestFixture {
  using ProblemSpace = std::vector<std::pair<int64_t, uint64_t>>;

  static constexpr int const a = 5;
  static constexpr int const b = 7;

  ProblemSpace getExperimentValues() const override {
    ProblemSpace problemSpace;

    for (int64_t i = 2; i < (2 << 10); i *= 2) {
      problemSpace.emplace_back(i, 0);
    }

    return problemSpace;
  }

  void setUp(int64_t experimentValue) {
    array.resize(experimentValue);

    std::generate(begin(array), end(array), std::rand);
  }

  void tearDown() {
    array.clear();
  }

  std::vector<int> array;

};

static constexpr int const Samples = 2000;
static constexpr int const Iterations = 2000;

static auto const lX = LeL::Placeholders::_x;

BASELINE_F(IncreasingComplecity_0, Lambda, Fixture, Samples, Iterations) {
  auto expression = [] (auto x) { return a*x; };

  std::transform(array.begin(), array.end(), array.begin(), expression);
}

BASELINE_F(IncreasingComplecity_1, Lambda, Fixture, Samples, Iterations) {
  auto expression = [](auto x) { return a * x - x; };

  std::transform(array.begin(), array.end(), array.begin(), expression);
}

BASELINE_F(IncreasingComplecity_2, Lambda, Fixture, Samples, Iterations) {
  auto expression = [](auto x) { return a * x - (a + x); };

  std::transform(array.begin(), array.end(), array.begin(), expression);
}

BASELINE_F(IncreasingComplecity_3, Lambda, Fixture, Samples, Iterations) {
  auto expression = [](auto x) {
    return (a * x - (a + x)) * (b * x - (b + x)) * (a * x - (b + x))
           * (b * x - (a + x));
  };

  std::transform(array.begin(), array.end(), array.begin(), expression);
}

BASELINE_F(IncreasingComplecity_4, Lambda, Fixture, Samples, Iterations) {
  auto expression = [](auto x) {
    return (a * x - (a + x)) * (b * x - (b + x)) * (a * x - (b + x))
             * (b * x - (a + x))
           - b * x + (b - a * x);
  };

  std::transform(array.begin(), array.end(), array.begin(), expression);
}

BENCHMARK_F(IncreasingComplecity_0, LeL, Fixture, Samples, Iterations) {
  auto expression = a * lX;

  std::transform(array.begin(), array.end(), array.begin(), expression);
}

BENCHMARK_F(IncreasingComplecity_1, LeL, Fixture, Samples, Iterations) {
  auto expression = a * lX - lX;

  std::transform(array.begin(), array.end(), array.begin(), expression);
}

BENCHMARK_F(IncreasingComplecity_2, LeL, Fixture, Samples, Iterations) {
  auto expression = a * lX - (a + lX);

  std::transform(array.begin(), array.end(), array.begin(), expression);
}

BENCHMARK_F(IncreasingComplecity_3, LeL, Fixture, Samples, Iterations) {
  auto expression = (a * lX - (a + lX)) * (b * lX - (b + lX))
                    * (a * lX - (b + lX)) * (b * lX - (a + lX));

  std::transform(array.begin(), array.end(), array.begin(), expression);
}

BENCHMARK_F(IncreasingComplecity_4, LeL, Fixture, Samples, Iterations) {
  auto expression = (a * lX - (a + lX)) * (b * lX - (b + lX))
                      * (a * lX - (b + lX)) * (b * lX - (a + lX))
                    - b * lX + (b - a * lX);

  std::transform(array.begin(), array.end(), array.begin(), expression);
}

#ifdef LEL_HAS_BOOST

#include <boost/lambda/lambda.hpp>

auto const bX = boost::lambda::_1;

BENCHMARK_F(IncreasingComplecity_0, BLL, Fixture, Samples, Iterations) {
  auto expression = a * bX;

  std::transform(array.begin(), array.end(), array.begin(), expression);
}

BENCHMARK_F(IncreasingComplecity_1, BLL, Fixture, Samples, Iterations) {
  auto expression = a * bX - bX;

  std::transform(array.begin(), array.end(), array.begin(), expression);
}

BENCHMARK_F(IncreasingComplecity_2, BLL, Fixture, Samples, Iterations) {
  auto expression = a * bX - (a + bX);

  std::transform(array.begin(), array.end(), array.begin(), expression);
}

BENCHMARK_F(IncreasingComplecity_3, BLL, Fixture, Samples, Iterations) {
  auto expression = (a * bX - (a + bX)) * (b * bX - (b + bX))
                    * (a * bX - (b + bX)) * (b * bX - (a + bX));

  std::transform(array.begin(), array.end(), array.begin(), expression);
}

BENCHMARK_F(IncreasingComplecity_4, BLL, Fixture, Samples, Iterations) {
  auto expression = (a * bX - (a + bX)) * (b * bX - (b + bX))
                      * (a * bX - (b + bX)) * (b * bX - (a + bX))
                    - b * bX + (b - a * bX);

  std::transform(array.begin(), array.end(), array.begin(), expression);
}

#endif  // LEL_HAS_BOOST
