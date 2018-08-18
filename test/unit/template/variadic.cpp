// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/template/variadic.hpp"

#include "gtest/gtest.h"

#include "lel_test.hpp"

TEST(variadic_test, variadic_get_can_be_used_in_constexpr) {
  static_assert(
    LeL::Template::Variadic::Get<0>::Value(11, 22, 33, 44, 55) == 11, "");
  static_assert(
    LeL::Template::Variadic::Get<1>::Value(11, 22, 33, 44, 55) == 22, "");
  static_assert(
    LeL::Template::Variadic::Get<2>::Value(11, 22, 53, 46, 55) == 53, "");
  static_assert(
    LeL::Template::Variadic::Get<3>::Value(11, 22, 33, 46, 55) == 46, "");
}

TEST(variadic_test, variadic_get_returns_proper_value) {
  ASSERT_EQ(11, LeL::Template::Variadic::Get<0>::Value(11, 22, 33, 44, 55));
  ASSERT_EQ(22, LeL::Template::Variadic::Get<1>::Value(11, 22, 33, 44, 55));
  ASSERT_EQ(53, LeL::Template::Variadic::Get<2>::Value(11, 22, 53, 46, 55));
  ASSERT_EQ(46, LeL::Template::Variadic::Get<3>::Value(11, 22, 33, 46, 55));
}
