// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel.hpp"

#include <memory>
#include <vector>

#include "gtest/gtest.h"

class nested_single_std_placeholder_test : public ::testing::Test {
 protected:
  lel::placeholder<'x'> _x;
};


TEST_F(nested_single_std_placeholder_test, can_be_nested) {
  auto condition = _x * 4 - 1 > 5;

  ASSERT_TRUE(condition(5));
}

TEST_F(nested_single_std_placeholder_test, same_can_be_used_multiple_times) {
  auto condition = 2 + _x * 2 < 3 * _x;
  auto value = _x * _x;
  auto operation = _x * _x - _x <= _x * 2 + _x;

  ASSERT_TRUE(condition(5));
  ASSERT_EQ(9, value(3));
  ASSERT_TRUE(operation(2));
}
