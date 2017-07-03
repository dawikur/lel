// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel.hpp"

#include "gtest/gtest.h"

class nested_double_std_placeholder_test : public ::testing::Test {
 protected:
  Lel::Placeholder<'x'> _x;
  Lel::Placeholder<'y'> _y;
  Lel::Placeholder<'z'> _z;
};

TEST_F(nested_double_std_placeholder_test, can_use_multiple_std_placeholders) {
  auto value = 2 + _y * 2 - 3 * _x;

  ASSERT_EQ(2 + 3 * 2 - 3 * 5, value(5, 3));
}

TEST_F(nested_double_std_placeholder_test, can_be_used_multiple_times) {
  auto value = 1 + _x * 3 - _y * _y + _x * _z;

  ASSERT_EQ(1 + 2 * 3 - 4 * 4 + 2 * 6, value(2, 4, 6));
}
