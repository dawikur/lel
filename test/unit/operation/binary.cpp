// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/operation/binary.hpp"

#include "gtest/gtest.h"

TEST(binary_test, operator_plus_can_be_used_in_constexpr) {
  std::plus<> plus;

  static_assert(plus(1, 3) == 4, "");
}

TEST(binary_test, shiftleft_can_be_used_in_constexpr) {
  LeL::Operation::__ShiftLeft shift_left;

  static_assert(shift_left(1, 3) == 8, "");
}

