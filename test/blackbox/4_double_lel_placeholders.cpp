// Copyright 2007, Dawid Kurek, <dawikur@gmail.com>

#include "lel.hpp"

#include <memory>
#include <vector>

#include "gtest/gtest.h"

class double_lel_placeholders_test : public ::testing::Test {
 protected:
  lel::placeholder<'1'> _1;
  lel::placeholder<'2'> _2;
  lel::placeholder<'3'> _3;
  lel::placeholder<'x'> _x;
  lel::placeholder<'y'> _y;
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

TEST_F(double_lel_placeholders_test, double_index_vector_of_unique_ptr) {
  auto arr1 = *(_x[_y]);
  auto arr2 = *(_y[_x]);

  auto vec = std::vector<std::unique_ptr<int>>();
  vec.push_back(std::make_unique<int>(5));
  vec.push_back(std::make_unique<int>(4));

  ASSERT_EQ(5, arr1(vec, 0));
  ASSERT_EQ(4, arr2(1, vec));
}

TEST_F(double_lel_placeholders_test, double_index_unique_ptr_of_vector) {
  auto arr1 = (*_x)[_y];
  auto arr2 = (*_y)[_x];

  auto ptr = std::make_unique<std::vector<int>>();
  ptr->push_back(5);
  ptr->push_back(4);

  ASSERT_EQ(5, arr1(ptr, 0));
  ASSERT_EQ(4, arr2(1, ptr));
}

TEST_F(double_lel_placeholders_test, combine_indirection_and_address_of) {
  int value = 6;

  ASSERT_EQ(6, (*&_x)(value));
  ASSERT_EQ(&value, (&*&_x)(value));
  ASSERT_EQ(6, (*&*&_x)(value));
}

TEST_F(double_lel_placeholders_test, two_values_will_be_updated) {
  auto update = ++_x < ++_y;

  int x = 2;
  int y = 8;

  update(x, y);

  ASSERT_EQ(3, x);
  ASSERT_EQ(9, y);
}
