// Copyright 2007, Dawid Kurek, <dawikur@gmail.com>

#include "lel.hpp"

#include <memory>
#include <vector>

#include "gtest/gtest.h"

class double_std_placeholders_test : public ::testing::Test {
 protected:
  LeL::Placeholder<'1'> _1;
  LeL::Placeholder<'2'> _2;
  LeL::Placeholder<'3'> _3;
  LeL::Placeholder<'x'> _x;
  LeL::Placeholder<'y'> _y;
};

TEST_F(double_std_placeholders_test, equal_returns_true_for_same_values) {
  auto condition1 = _x == _y;
  auto condition2 = _y == _x;

  ASSERT_TRUE(condition1(5, 5));
  ASSERT_TRUE(condition2(2, 2));
}

TEST_F(double_std_placeholders_test, equal_returns_false_for_different_values) {
  auto condition1 = _x == _y;
  auto condition2 = _y == _x;

  ASSERT_FALSE(condition1(0, 1));
  ASSERT_FALSE(condition2(9, 7));
}

TEST_F(double_std_placeholders_test, not_equal_returns_true_for_different_values) {
  auto condition1 = _x != _y;
  auto condition2 = _y != _x;

  ASSERT_TRUE(condition1(4, 6));
  ASSERT_TRUE(condition2(2, 4));
}

TEST_F(double_std_placeholders_test, not_equal_returns_false_for_same_values) {
  auto condition1 = _x != _y;
  auto condition2 = _y != _x;

  ASSERT_FALSE(condition1(1, 1));
  ASSERT_FALSE(condition2(2, 2));
}

TEST_F(double_std_placeholders_test, greater_returns_true_for_greater_values) {
  auto condition1 = _1 > _2;
  auto condition2 = _2 > _1;

  ASSERT_TRUE(condition1(2, 1));
  ASSERT_TRUE(condition2(4, 7));
}

TEST_F(double_std_placeholders_test, greater_returns_false_for_less_or_equal_values) {
  auto condition1 = _1 > _2;
  auto condition2 = _2 > _1;

  ASSERT_FALSE(condition1(2, 2));
  ASSERT_FALSE(condition1(2, 3));
  ASSERT_FALSE(condition2(2, 2));
  ASSERT_FALSE(condition2(3, 2));
}

TEST_F(double_std_placeholders_test, less_returns_true_for_less_values) {
  auto condition1 = _1 < _2;
  auto condition2 = _2 < _1;

  ASSERT_TRUE(condition1(3, 4));
  ASSERT_TRUE(condition2(4, 3));
}

TEST_F(double_std_placeholders_test, less_returns_false_for_greater_or_equal_values) {
  auto condition1 = _1 < _2;
  auto condition2 = _2 < _1;

  ASSERT_FALSE(condition1(4, 4));
  ASSERT_FALSE(condition1(4, 3));
  ASSERT_FALSE(condition2(4, 4));
  ASSERT_FALSE(condition2(3, 4));
}

TEST_F(double_std_placeholders_test, greater_eq_returns_true_for_greater_or_equal_values) {
  auto condition1 = _1 >= _2;
  auto condition2 = _2 >= _1;

  ASSERT_TRUE(condition1(2, 2));
  ASSERT_TRUE(condition1(2, 1));
  ASSERT_TRUE(condition2(2, 2));
  ASSERT_TRUE(condition2(1, 2));
}

TEST_F(double_std_placeholders_test, greater_eq_returns_false_for_less_values) {
  auto condition1 = _1 >= _2;
  auto condition2 = _2 >= _1;

  ASSERT_FALSE(condition1(2, 4));
  ASSERT_FALSE(condition2(4, 2));
}

TEST_F(double_std_placeholders_test, less_eq_returns_true_for_less_or_equal_values) {
  auto condition1 = _1 <= _2;
  auto condition2 = _2 <= _1;

  ASSERT_TRUE(condition1(2, 2));
  ASSERT_TRUE(condition1(1, 2));
  ASSERT_TRUE(condition2(2, 2));
  ASSERT_TRUE(condition2(2, 1));
}

TEST_F(double_std_placeholders_test, less_eq_returns_false_for_greater_values) {
  auto condition1 = _1 <= _2;
  auto condition2 = _2 <= _1;

  ASSERT_FALSE(condition1(2, 1));
  ASSERT_FALSE(condition2(1, 2));
}

TEST_F(double_std_placeholders_test, plus_adds_values) {
  auto operation1 = _x + _y;
  auto operation2 = _y + _x;

  ASSERT_EQ(3, operation1(2, 1));
  ASSERT_EQ(4, operation2(1, 3));
}

TEST_F(double_std_placeholders_test, minus_removes_values) {
  auto operation1 = _1 - _2;
  auto operation2 = _2 - _1;

  ASSERT_EQ(3, operation1(7, 4));
  ASSERT_EQ(-2, operation2(5, 3));
}

TEST_F(double_std_placeholders_test, multplies_increases_values) {
  auto operation1 = _x * _y;
  auto operation2 = _y * _x;

  ASSERT_EQ(10, operation1(2, 5));
  ASSERT_EQ(3, operation2(3, 1));
}

TEST_F(double_std_placeholders_test, divies_returns_proper_value) {
  auto operation1 = _1 / _2;
  auto operation2 = _2 / _1;

  ASSERT_DOUBLE_EQ(2.5, operation1(5, 2.0));
  ASSERT_EQ(0.5, operation2(8.0, 4));
}

TEST_F(double_std_placeholders_test, modulus_returns_modulo) {
  auto operation1 = _1 % _2;
  auto operation2 = _3 % _1;

  ASSERT_EQ(2, operation1(8, 3));
  ASSERT_EQ(2, operation2(5, 7));
}

TEST_F(double_std_placeholders_test, logical_and) {
  auto and1 = _x && _y;
  auto and2 = _y && _x;

  ASSERT_TRUE(and1(true, true));
  ASSERT_FALSE(and1(false, true));
  ASSERT_FALSE(and2(false, false));
  ASSERT_FALSE(and2(true, false));
}

TEST_F(double_std_placeholders_test, logical_or) {
  auto or1 = _x || _y;
  auto or2 = _y || _x;

  ASSERT_TRUE(or1(true, true));
  ASSERT_TRUE(or1(false, true));
  ASSERT_TRUE(or2(false, true));
  ASSERT_FALSE(or2(false, false));
}

TEST_F(double_std_placeholders_test, bit_and) {
  auto and1 = _x & _y;
  auto and2 = _y & _x;

  ASSERT_EQ(4, and1(5, 12));
  ASSERT_EQ(1, and2(1, 9));
}

TEST_F(double_std_placeholders_test, bit_or) {
  auto or1 = _x | _y;
  auto or2 = _y | _x;

  ASSERT_EQ(11, or1(2, 9));
  ASSERT_EQ(13, or2(4, 9));
}
