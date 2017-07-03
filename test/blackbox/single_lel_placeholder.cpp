// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel.hpp"

#include "gtest/gtest.h"

class single_lel_placeholder_test : public ::testing::Test {
 protected:
  Lel::Placeholder<'x'> _x;
};

TEST_F(single_lel_placeholder_test, subscription_on_array) {
  auto value = _x[3];

  int array[5] = {2, 4, 5, 7, 3};

  ASSERT_EQ(array[3], value(array));
}

TEST_F(single_lel_placeholder_test, subscriptino_on_vector) {
  auto value = _x[4];

  std::vector<int> vec{0, 3, 6, 9, 12, 15};

  ASSERT_EQ(vec[4], value(vec));
}

TEST_F(single_lel_placeholder_test, shift_left) {
  auto value1 = _x << 2;
  auto value2 = 1 << _x;

  ASSERT_EQ(8, value1(2));
  ASSERT_EQ(4, value2(2));
}

TEST_F(single_lel_placeholder_test, shift_right) {
  auto value1 = _x >> 2;
  auto value2 = 7 >> _x;

  ASSERT_EQ(2, value1(8));
  ASSERT_EQ(1, value2(2));
}

