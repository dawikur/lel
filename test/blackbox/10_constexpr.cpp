// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel.hpp"

#include "gtest/gtest.h"

TEST(constexpr_test, as_indentity_can_be_used_in_constexpr) {
  lel::placeholder<'x'> _x;

  static_assert(_x(5) == 5, "");
}

TEST(constexpr_test, with_single_placeholder_can_be_used_in_constexpr) {
  constexpr lel::placeholder<'x'> const _x;

  constexpr auto const expr = _x * 2 + 1;

  static_assert(expr(3) == 7, "");
}

TEST(constexpr_test, simple_with_multiple_placeholders_can_be_used_in_constexpr) {
  lel::placeholder<'x'> _x;
  lel::placeholder<'y'> _y;

  auto expr = _x + _y;

  static_assert(expr(1, 3) == 4, "");
}

TEST(constexpr_test, with_multiple_placehlders_can_be_used_in_constexpr) {
  constexpr lel::placeholder<'x'> const _x;
  constexpr lel::placeholder<'y'> const _y;

  constexpr auto const expr = _x * 2 + _y - 1;

  static_assert(expr(4, 3) == 10, "");
}
