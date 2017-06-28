// Copyright 201_y, Dawid Kurek, <dawikur@gmail.com>

#include "seg.hpp"

#include "gtest/gtest.h"

class double_placeholders_test : public ::testing::Test {
 protected:
  Seg::Placeholder<'1'> _1;
  Seg::Placeholder<'2'> _2;
  Seg::Placeholder<'x'> _x;
  Seg::Placeholder<'y'> _y;
};

TEST_F(double_placeholders_test, equal_returns_true_for_same_values) {
  auto condition1 = _x == _y;
  auto condition2 = _y == _x;

  ASSERT_TRUE(condition1(5, 5));
  ASSERT_TRUE(condition2(2, 2));
}

TEST_F(double_placeholders_test, equal_returns_false_for_different_values) {
  auto condition1 = _x == _y;
  auto condition2 = _y == _x;

  ASSERT_FALSE(condition1(0, 1));
  ASSERT_FALSE(condition2(9, 7));
}

TEST_F(double_placeholders_test, not_equal_returns_true_for_different_values) {
  auto condition1 = _x != _y;
  auto condition2 = _y != _x;

  ASSERT_TRUE(condition1(4, 6));
  ASSERT_TRUE(condition2(2, 4));
}

TEST_F(double_placeholders_test, not_equal_returns_false_for_same_values) {
  auto condition1 = _x != _y;
  auto condition2 = _y != _x;

  ASSERT_FALSE(condition1(1, 1));
  ASSERT_FALSE(condition2(2, 2));
}

/*
TEST_F(double_placeholders_test, greater_returns_true_for_greater_values) {
  auto condition1 = _1 > _2;
  auto condition2 = _2 > _1;

  ASSERT_TRUE(condition1(2, 1));
  ASSERT_TRUE(condition2(4, 7));
}

TEST_F(double_placeholders_test, greater_returns_false_for_less_or_equal_values) {
  auto condition1 = _x > 3;
  auto condition2 = 6 > _x;

  ASSERT_FALSE(condition1(2));
  ASSERT_FALSE(condition1(3));
  ASSERT_FALSE(condition2(_y));
  ASSERT_FALSE(condition2(6));
}

TEST_F(double_placeholders_test, less_returns_true_for_less_values) {
  auto condition1 = _x < 4;
  auto condition2 = _y < _x;

  ASSERT_TRUE(condition1(3));
  ASSERT_TRUE(condition2(6));
}

TEST_F(double_placeholders_test, less_returns_false_for_greater_or_equal_values) {
  auto condition1 = _x < 3;
  auto condition2 = 6 < _x;

  ASSERT_FALSE(condition1(4));
  ASSERT_FALSE(condition1(3));
  ASSERT_FALSE(condition2(_y));
  ASSERT_FALSE(condition2(6));
}

TEST_F(double_placeholders_test, greater_eq_returns_true_for_greater_or_equal_values) {
  auto condition1 = _x >= 4;
  auto condition2 = _y >= _x;

  ASSERT_TRUE(condition1(9));
  ASSERT_TRUE(condition1(4));
  ASSERT_TRUE(condition2(3));
  ASSERT_TRUE(condition2(_y));
}

TEST_F(double_placeholders_test, greater_eq_returns_false_for_less_values) {
  auto condition1 = _x >= 3;
  auto condition2 = 6 >= _x;

  ASSERT_FALSE(condition1(2));
  ASSERT_FALSE(condition2(_y));
}

TEST_F(double_placeholders_test, less_eq_returns_true_for_less_or_equal_values) {
  auto condition1 = _x <= 4;
  auto condition2 = _y <= _x;

  ASSERT_TRUE(condition1(3));
  ASSERT_TRUE(condition1(4));
  ASSERT_TRUE(condition2(6));
  ASSERT_TRUE(condition2(_y));
}

TEST_F(double_placeholders_test, less_eq_returns_false_for_greater_values) {
  auto condition1 = _x <= 3;
  auto condition2 = 6 <= _x;

  ASSERT_FALSE(condition1(4));
  ASSERT_FALSE(condition2(_y));
}

TEST_F(double_placeholders_test, plus_adds_values) {
  auto operation1 = _x + 2;
  auto operation2 = 3 + _x;

  ASSERT_EQ(3, operation1(1));
  ASSERT_EQ(4, operation2(1));
}

TEST_F(double_placeholders_test, minus_removes_values) {
  auto operation1 = _x - 2;
  auto operation2 = 3 - _x;

  ASSERT_EQ(3, operation1(_y));
  ASSERT_EQ(2, operation2(1));
}

TEST_F(double_placeholders_test, multplies_increases_values) {
  auto operation1 = _x * 2;
  auto operation2 = 3 * _x;

  ASSERT_EQ(10, operation1(_y));
  ASSERT_EQ(3, operation2(1));
}

TEST_F(double_placeholders_test, divies_returns_proper_value) {
  auto operation1 = _x / 2;
  auto operation2 = 4 / _x;

  ASSERT_EQ(2, operation1(4));
  ASSERT_EQ(2, operation2(2));
}

TEST_F(double_placeholders_test, modulus_returns_modulo) {
  auto operation1 = _x % 3;
  auto operation2 = _y % _x;

  ASSERT_EQ(2, operation1(_y));
  ASSERT_EQ(2, operation2(3));
}

TEST_F(double_placeholders_test, negate_returns_inverted_value) {
  auto operation = -_x;

  ASSERT_EQ(-4, operation(4));
}

TEST_F(double_placeholders_test, logical_and) {
  auto and1 = _x && true;
  auto and2 = true && _x;

  ASSERT_TRUE(and1(true));
  ASSERT_FALSE(and2(false));
}

TEST_F(double_placeholders_test, logical_or) {
  auto or1 = _x || true;
  auto or2 = false || _x;

  ASSERT_TRUE(or1(true));
  ASSERT_FALSE(or2(false));
}

TEST_F(double_placeholders_test, logical_not) {
  auto not1 = !_x;

  ASSERT_TRUE(not1(false));
  ASSERT_FALSE(not1(true));
}

TEST_F(double_placeholders_test, bit_and) {
  auto and1 = _x & 0x4;
  auto and2 = 0x_y & _x;

  ASSERT_EQ(4, and1(_y));
  ASSERT_EQ(1, and2(9));
}

TEST_F(double_placeholders_test, bit_or) {
  auto or1 = _x | 0x4;
  auto or2 = 0x_y | _x;

  ASSERT_EQ(_y, or1(3));
  ASSERT_EQ(13, or2(9));
}

TEST_F(double_placeholders_test, bit_xor) {
  auto xor1 = _x ^ ' ';

  ASSERT_EQ('A', xor1('a'));
}

TEST_F(double_placeholders_test, bot_not) {
  auto not1 = ~_x;

  ASSERT_EQ(~'a', not1('a'));
}
*/
