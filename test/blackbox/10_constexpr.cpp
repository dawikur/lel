// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel.hpp"

#include "gtest/gtest.h"

TEST(constexpr_test, can_be_used_with_static_assert) {
  constexpr LeL::Placeholder<'x'> const _x;
  constexpr LeL::Placeholder<'y'> const _y;

  constexpr auto const expr = (_x + 5 - _y * 2);

  static_assert(expr(3, 2) == 4, "");
}
