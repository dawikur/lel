// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel_benchmark.hpp"

TEST(BASELINE, 1, 1, Lambda, [](auto a)                                         { return, ; },  a, 23, 29, 31, 37, 43, 19)

TEST(BASELINE, 1, 2, Lambda, [](auto a)                                         { return, ; },  a,  a, 29, 31, 37, 43, 19)
TEST(BASELINE, 2, 2, Lambda, [](auto a, auto b)                                 { return, ; },  a,  b, 29, 31, 37, 43, 19, 23)

TEST(BASELINE, 1, 3, Lambda, [](auto a)                                         { return, ; },  a,  a,  a, 31, 37, 43, 19)
TEST(BASELINE, 2, 3, Lambda, [](auto a, auto b)                                 { return, ; },  a,  b,  a, 31, 37, 43, 19, 23)
TEST(BASELINE, 3, 3, Lambda, [](auto a, auto b, auto c)                         { return, ; },  a,  b,  c, 31, 37, 43, 19, 23, 29)

TEST(BASELINE, 1, 4, Lambda, [](auto a)                                         { return, ; },  a,  a,  a,  a, 37, 43, 19)
TEST(BASELINE, 2, 4, Lambda, [](auto a, auto b)                                 { return, ; },  a,  b,  a,  b, 37, 43, 19, 23)
TEST(BASELINE, 3, 4, Lambda, [](auto a, auto b, auto c)                         { return, ; },  a,  b,  c,  b, 37, 43, 19, 23, 29)
TEST(BASELINE, 4, 4, Lambda, [](auto a, auto b, auto c, auto d)                 { return, ; },  a,  b,  c,  d, 37, 43, 19, 23, 29, 31)

TEST(BASELINE, 1, 5, Lambda, [](auto a)                                         { return, ; },  a,  a,  a,  a,  a, 43, 19)
TEST(BASELINE, 2, 5, Lambda, [](auto a, auto b)                                 { return, ; },  a,  b,  a,  b,  b, 43, 19, 23)
TEST(BASELINE, 3, 5, Lambda, [](auto a, auto b, auto c)                         { return, ; },  a,  b,  c,  b,  c, 43, 19, 23, 29)
TEST(BASELINE, 4, 5, Lambda, [](auto a, auto b, auto c, auto d)                 { return, ; },  a,  b,  c,  d,  c, 43, 19, 23, 29, 31)
TEST(BASELINE, 5, 5, Lambda, [](auto a, auto b, auto c, auto d, auto e)         { return, ; },  a,  b,  c,  d,  e, 43, 19, 23, 29, 31, 37)

TEST(BASELINE, 1, 6, Lambda, [](auto a)                                         { return, ; },  a,  a,  a,  a,  a,  a, 19)
TEST(BASELINE, 2, 6, Lambda, [](auto a, auto b)                                 { return, ; },  a,  b,  a,  b,  b,  a, 19, 23)
TEST(BASELINE, 3, 6, Lambda, [](auto a, auto b, auto c)                         { return, ; },  a,  b,  c,  b,  c,  c, 19, 23, 29)
TEST(BASELINE, 4, 6, Lambda, [](auto a, auto b, auto c, auto d)                 { return, ; },  a,  b,  c,  d,  c,  d, 19, 23, 29, 31)
TEST(BASELINE, 5, 6, Lambda, [](auto a, auto b, auto c, auto d, auto e)         { return, ; },  a,  b,  c,  d,  e,  d, 19, 23, 29, 31, 37)
TEST(BASELINE, 6, 6, Lambda, [](auto a, auto b, auto c, auto d, auto e, auto f) { return, ; },  a,  b,  c,  d,  e,  f, 19, 23, 29, 31, 37, 43)

namespace LeL {
  using namespace lel;

  TEST(BENCHMARK, 1, 1, LeL, , , _a, 23, 29, 31, 37, 43, 19)

  TEST(BENCHMARK, 1, 2, LeL, , , _a, _a, 29, 31, 37, 43, 19)
  TEST(BENCHMARK, 2, 2, LeL, , , _a, _b, 29, 31, 37, 43, 19, 23)

  TEST(BENCHMARK, 1, 3, LeL, , , _a, _a, _a, 31, 37, 43, 19)
  TEST(BENCHMARK, 2, 3, LeL, , , _a, _b, _a, 31, 37, 43, 19, 23)
  TEST(BENCHMARK, 3, 3, LeL, , , _a, _b, _c, 31, 37, 43, 19, 23, 29)

  TEST(BENCHMARK, 1, 4, LeL, , , _a, _a, _a, _a, 37, 43, 19)
  TEST(BENCHMARK, 2, 4, LeL, , , _a, _b, _a, _b, 37, 43, 19, 23)
  TEST(BENCHMARK, 3, 4, LeL, , , _a, _b, _c, _b, 37, 43, 19, 23, 29)
  TEST(BENCHMARK, 4, 4, LeL, , , _a, _b, _c, _d, 37, 43, 19, 23, 29, 31)

  TEST(BENCHMARK, 1, 5, LeL, , , _a, _a, _a, _a, _a, 43, 19)
  TEST(BENCHMARK, 2, 5, LeL, , , _a, _b, _a, _b, _b, 43, 19, 23)
  TEST(BENCHMARK, 3, 5, LeL, , , _a, _b, _c, _b, _c, 43, 19, 23, 29)
  TEST(BENCHMARK, 4, 5, LeL, , , _a, _b, _c, _d, _c, 43, 19, 23, 29, 31)
  TEST(BENCHMARK, 5, 5, LeL, , , _a, _b, _c, _d, _e, 43, 19, 23, 29, 31, 37)

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

  TEST(BENCHMARK, 1, 1, BLL, , , _1, 23, 29, 31, 37, 43, 19)

  TEST(BENCHMARK, 1, 2, BLL, , , _1, _1, 29, 31, 37, 43, 19)
  TEST(BENCHMARK, 2, 2, BLL, , , _1, _2, 29, 31, 37, 43, 19, 23)

  TEST(BENCHMARK, 1, 3, BLL, , , _1, _1, _1, 31, 37, 43, 19)
  TEST(BENCHMARK, 2, 3, BLL, , , _1, _2, _1, 31, 37, 43, 19, 23)
  TEST(BENCHMARK, 3, 3, BLL, , , _1, _2, _3, 31, 37, 43, 19, 23, 29)

  TEST(BENCHMARK, 1, 4, BLL, , , _1, _1, _1, _1, 37, 43, 19)
  TEST(BENCHMARK, 2, 4, BLL, , , _1, _2, _1, _2, 37, 43, 19, 23)
  TEST(BENCHMARK, 3, 4, BLL, , , _1, _2, _3, _2, 37, 43, 19, 23, 29)

  TEST(BENCHMARK, 1, 5, BLL, , , _1, _1, _1, _1, _1, 43, 19)
  TEST(BENCHMARK, 2, 5, BLL, , , _1, _2, _1, _2, _2, 43, 19, 23)
  TEST(BENCHMARK, 3, 5, BLL, , , _1, _2, _3, _2, _3, 43, 19, 23, 29)

  TEST(BENCHMARK, 1, 6, BLL, , , _1, _1, _1, _1, _1, _1, 19)
  TEST(BENCHMARK, 2, 6, BLL, , , _1, _2, _1, _2, _2, _1, 19, 23)
  TEST(BENCHMARK, 3, 6, BLL, , , _1, _2, _3, _2, _3, _3, 19, 23, 29)
}

#endif  // LEL_HAS_BOOST

CELERO_MAIN
