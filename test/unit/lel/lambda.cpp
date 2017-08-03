// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/lambda.hpp"

#include "gtest/gtest.h"

#include "lel.hpp"

TEST(lambda_test, as_indentity_can_be_used_in_constexpr) {
  LeL::Placeholder<'x'> _x;

  static_assert(_x(5) == 5, "");
}

TEST(lambda_test, with_single_placeholder_can_be_used_in_constexpr) {
  constexpr LeL::Placeholder<'x'> const _x;

  constexpr auto const expr = _x * 2 + 1;

  static_assert(expr(3) == 7, "");
}

TEST(lambda_test, simple_with_multiple_placeholders_can_be_used_in_constexpr) {
  LeL::Placeholder<'x'> _x;
  LeL::Placeholder<'y'> _y;

  auto expr = _x + _y;

  static_assert(expr(1, 3) == 4, "");
}

TEST(lambda_test, with_multiple_placehlders_can_be_used_in_constexpr) {
  constexpr LeL::Placeholder<'x'> const _x;
  constexpr LeL::Placeholder<'y'> const _y;

  constexpr auto const expr = _x * 2 + _y - 1;

  static_assert(expr(4, 3) == 10, "");
}
