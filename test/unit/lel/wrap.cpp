// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/wrap.hpp"

#include "gtest/gtest.h"

TEST(wrap_test, wrap_value_can_be_used_in_constexpr) {
  constexpr LeL::Wrap<int> const wrap(5);

  static_assert(wrap() == 5, "");
}

