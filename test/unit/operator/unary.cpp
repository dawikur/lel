// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/operator/unary.hpp"

#include "gtest/gtest.h"

TEST(unary_test, logical_not_can_be_used_in_constexpr) {
  std::logical_not<> logical_not;

  static_assert(logical_not(false), "");
}
