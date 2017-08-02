// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel.hpp"

#include "gtest/gtest.h"

class curring_test : public ::testing::Test {
 protected:
  LeL::Placeholder<'x'> _x;
  LeL::Placeholder<'y'> _y;
  LeL::Placeholder<'z'> _z;
};

TEST_F(curring_test, add_one) {
  auto add_values = _x + _y;
  auto add_one = add_values(1);

  ASSERT_EQ(6, add_one(5));
}

TEST_F(curring_test, sum_of_three) {
  auto sum_of_three = _x + _y + _z;

  ASSERT_EQ(12, sum_of_three(2, 6, 4));
  ASSERT_EQ(12, sum_of_three(2, 6)(4));
  ASSERT_EQ(12, sum_of_three(2)(6, 4));
  ASSERT_EQ(12, sum_of_three(2)(6)(4));
}

TEST_F(curring_test, replacing_multiple_instances_of_the_same_placeholder) {
  auto complex = _x - _y + _y * _z;

  ASSERT_EQ(5, complex(1, 2, 3));
  ASSERT_EQ(5, complex(1)(2, 3));
  ASSERT_EQ(5, complex(1, 2)(3));
  ASSERT_EQ(5, complex(1)(2)(3));
}
