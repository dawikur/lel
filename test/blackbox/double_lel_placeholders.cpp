// Copyright 2007, Dawid Kurek, <dawikur@gmail.com>

#include "lel.hpp"

#include "gtest/gtest.h"

class double_lel_placeholders_test : public ::testing::Test {
 protected:
  Lel::Placeholder<'1'> _1;
  Lel::Placeholder<'2'> _2;
  Lel::Placeholder<'3'> _3;
  Lel::Placeholder<'x'> _x;
  Lel::Placeholder<'y'> _y;
};

TEST_F(double_lel_placeholders_test, shift_left) {
  auto value1 = _x << _y;
  auto value2 = _y << _x;

  ASSERT_EQ(8, value1(2, 2));
  ASSERT_EQ(4, value2(2, 1));
}

TEST_F(double_lel_placeholders_test, shift_right) {
  auto value1 = _x >> _y;
  auto value2 = _y >> _x;

  ASSERT_EQ(2, value1(8, 2));
  ASSERT_EQ(1, value2(2, 7));
}

TEST_F(double_lel_placeholders_test, both_array_and_index) {
  auto arr1 = _x[_y];
  auto arr2 = _y[_x];

  int array[5] = {2, 3, 5, 4, 1};

  ASSERT_EQ(4, arr1(array, 3));
  ASSERT_EQ(5, arr2(2, array));
}

TEST_F(double_lel_placeholders_test, both_array_and_index_with_vector) {
  auto arr1 = _x[_y];
  auto arr2 = _y[_x];

  auto vec = std::vector<int>();
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(5);
  vec.push_back(4);
  vec.push_back(1);

  ASSERT_EQ(4, arr1(vec, 3));
  ASSERT_EQ(5, arr2(2, vec));
}

