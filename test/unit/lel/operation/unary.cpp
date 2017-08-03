// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/operation/unary.hpp"

#include "gtest/gtest.h"

TEST(unary_test, logical_not_can_be_used_in_constexpr) {
  std::logical_not<> logical_not;

  static_assert(logical_not(false), "");
}

TEST(unary_test, indirection_can_be_used_in_constexpr) {
  LeL::Operation::__Indirection indirection;

  int const val = 5;

  static_assert(indirection(&val) == 5, "");
}
