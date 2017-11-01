// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel_benchmark.hpp"

TEST(BASELINE, 1, 6, Lambda, [](auto a)                                         { return, ; }, a, a, a, a, a, a, 19)
TEST(BASELINE, 2, 6, Lambda, [](auto a, auto b)                                 { return, ; }, a, b, a, b, b, a, 19, 23)
TEST(BASELINE, 3, 6, Lambda, [](auto a, auto b, auto c)                         { return, ; }, a, b, c, b, c, c, 19, 23, 29)
TEST(BASELINE, 4, 6, Lambda, [](auto a, auto b, auto c, auto d)                 { return, ; }, a, b, c, d, c, d, 19, 23, 29, 31)
TEST(BASELINE, 5, 6, Lambda, [](auto a, auto b, auto c, auto d, auto e)         { return, ; }, a, b, c, d, e, d, 19, 23, 29, 31, 37)
TEST(BASELINE, 6, 6, Lambda, [](auto a, auto b, auto c, auto d, auto e, auto f) { return, ; }, a, b, c, d, e, f, 19, 23, 29, 31, 37, 43)

namespace LeL {
  using namespace Placeholders;

  TEST(BENCHMARK, 1, 6, LeL, , , _a, _a, _a, _a, _a, _a, 19)
  TEST(BENCHMARK, 2, 6, LeL, , , _a, _b, _a, _b, _b, _a, 19, 23)
  TEST(BENCHMARK, 3, 6, LeL, , , _a, _b, _c, _b, _c, _c, 19, 23, 29)
  TEST(BENCHMARK, 4, 6, LeL, , , _a, _b, _c, _d, _c, _d, 19, 23, 29, 31)
  TEST(BENCHMARK, 5, 6, LeL, , , _a, _b, _c, _d, _e, _d, 19, 23, 29, 31, 37)
  TEST(BENCHMARK, 6, 6, LeL, , , _a, _b, _c, _d, _e, _f, 19, 23, 29, 31, 37, 43)
}

#ifdef LEL_HAS_BOOST

namespace boost {
  using namespace lambda;

  TEST(BENCHMARK, 1, 6, BLL, , , _1, _1, _1, _1, _1, _1, 19)
  TEST(BENCHMARK, 2, 6, BLL, , , _1, _2, _1, _2, _2, _1, 19, 23)
  TEST(BENCHMARK, 3, 6, BLL, , , _1, _2, _3, _2, _3, _3, 19, 23, 29)
}

#endif  // LEL_HAS_BOOST

CELERO_MAIN
