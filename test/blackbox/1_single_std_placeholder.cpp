// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel.hpp"

#include <memory>
#include <vector>

#include "gtest/gtest.h"

class single_std_placeholder_test : public ::testing::Test {
 protected:
  LeL::Placeholder<'x'> _x;
};

TEST_F(single_std_placeholder_test, raw_placeholder_return_passed_value) {
  ASSERT_TRUE(_x(true));
  ASSERT_EQ(8, _x(8));
}

TEST_F(single_std_placeholder_test, equal_returns_true_for_same_values) {
  auto condition1 = _x == 5;
  auto condition2 = 2 == _x;

  ASSERT_TRUE(condition1(5));
  ASSERT_TRUE(condition2(2));
}

TEST_F(single_std_placeholder_test, equal_returns_false_for_different_values) {
  auto condition1 = _x == 7;
  auto condition2 = 8 == _x;

  ASSERT_FALSE(condition1(0));
  ASSERT_FALSE(condition2(9));
}

TEST_F(single_std_placeholder_test, not_equal_returns_true_for_different_values) {
  auto condition1 = _x != 5;
  auto condition2 = 2 != _x;

  ASSERT_TRUE(condition1(4));
  ASSERT_TRUE(condition2(4));
}

TEST_F(single_std_placeholder_test, not_equal_returns_false_for_same_values) {
  auto condition1 = _x != 5;
  auto condition2 = 2 != _x;

  ASSERT_FALSE(condition1(5));
  ASSERT_FALSE(condition2(2));
}

TEST_F(single_std_placeholder_test, greater_returns_true_for_greater_values) {
  auto condition1 = _x > 4;
  auto condition2 = 5 > _x;

  ASSERT_TRUE(condition1(9));
  ASSERT_TRUE(condition2(4));
}

TEST_F(single_std_placeholder_test, greater_returns_false_for_less_or_equal_values) {
  auto condition1 = _x > 3;
  auto condition2 = 6 > _x;

  ASSERT_FALSE(condition1(2));
  ASSERT_FALSE(condition1(3));
  ASSERT_FALSE(condition2(7));
  ASSERT_FALSE(condition2(6));
}

TEST_F(single_std_placeholder_test, less_returns_true_for_less_values) {
  auto condition1 = _x < 4;
  auto condition2 = 5 < _x;

  ASSERT_TRUE(condition1(3));
  ASSERT_TRUE(condition2(6));
}

TEST_F(single_std_placeholder_test, less_returns_false_for_greater_or_equal_values) {
  auto condition1 = _x < 3;
  auto condition2 = 6 < _x;

  ASSERT_FALSE(condition1(4));
  ASSERT_FALSE(condition1(3));
  ASSERT_FALSE(condition2(5));
  ASSERT_FALSE(condition2(6));
}

TEST_F(single_std_placeholder_test, greater_eq_returns_true_for_greater_or_equal_values) {
  auto condition1 = _x >= 4;
  auto condition2 = 5 >= _x;

  ASSERT_TRUE(condition1(9));
  ASSERT_TRUE(condition1(4));
  ASSERT_TRUE(condition2(3));
  ASSERT_TRUE(condition2(5));
}

TEST_F(single_std_placeholder_test, greater_eq_returns_false_for_less_values) {
  auto condition1 = _x >= 3;
  auto condition2 = 6 >= _x;

  ASSERT_FALSE(condition1(2));
  ASSERT_FALSE(condition2(7));
}

TEST_F(single_std_placeholder_test, less_eq_returns_true_for_less_or_equal_values) {
  auto condition1 = _x <= 4;
  auto condition2 = 5 <= _x;

  ASSERT_TRUE(condition1(3));
  ASSERT_TRUE(condition1(4));
  ASSERT_TRUE(condition2(6));
  ASSERT_TRUE(condition2(5));
}

TEST_F(single_std_placeholder_test, less_eq_returns_false_for_greater_values) {
  auto condition1 = _x <= 3;
  auto condition2 = 6 <= _x;

  ASSERT_FALSE(condition1(4));
  ASSERT_FALSE(condition2(5));
}

TEST_F(single_std_placeholder_test, plus_adds_values) {
  auto operation1 = _x + 2;
  auto operation2 = 3 + _x;

  ASSERT_EQ(3, operation1(1));
  ASSERT_EQ(4, operation2(1));
}

TEST_F(single_std_placeholder_test, minus_removes_values) {
  auto operation1 = _x - 2;
  auto operation2 = 3 - _x;

  ASSERT_EQ(3, operation1(5));
  ASSERT_EQ(2, operation2(1));
}

TEST_F(single_std_placeholder_test, multplies_increases_values) {
  auto operation1 = _x * 2;
  auto operation2 = 3 * _x;

  ASSERT_EQ(10, operation1(5));
  ASSERT_EQ(3, operation2(1));
}

TEST_F(single_std_placeholder_test, divies_returns_proper_value) {
  auto operation1 = _x / 2;
  auto operation2 = 4 / _x;

  ASSERT_EQ(2, operation1(4));
  ASSERT_EQ(2, operation2(2));
}

TEST_F(single_std_placeholder_test, modulus_returns_modulo) {
  auto operation1 = _x % 3;
  auto operation2 = 5 % _x;

  ASSERT_EQ(2, operation1(5));
  ASSERT_EQ(2, operation2(3));
}

TEST_F(single_std_placeholder_test, negate_returns_inverted_value) {
  auto operation = -_x;

  ASSERT_EQ(-4, operation(4));
}

TEST_F(single_std_placeholder_test, logical_and) {
  auto and1 = _x && true;
  auto and2 = true && _x;

  ASSERT_TRUE(and1(true));
  ASSERT_FALSE(and2(false));
}

TEST_F(single_std_placeholder_test, logical_or) {
  auto or1 = _x || true;
  auto or2 = false || _x;

  ASSERT_TRUE(or1(true));
  ASSERT_FALSE(or2(false));
}

TEST_F(single_std_placeholder_test, logical_not) {
  auto not1 = !_x;

  ASSERT_TRUE(not1(false));
  ASSERT_FALSE(not1(true));
}

TEST_F(single_std_placeholder_test, bit_and) {
  auto and1 = _x & 0x4;
  auto and2 = 0x5 & _x;

  ASSERT_EQ(4, and1(7));
  ASSERT_EQ(1, and2(9));
}

TEST_F(single_std_placeholder_test, bit_or) {
  auto or1 = _x | 0x4;
  auto or2 = 0x5 | _x;

  ASSERT_EQ(7, or1(3));
  ASSERT_EQ(13, or2(9));
}

TEST_F(single_std_placeholder_test, bit_xor) {
  auto xor1 = _x ^ ' ';

  ASSERT_EQ('A', xor1('a'));
}

TEST_F(single_std_placeholder_test, bot_not) {
  auto not1 = ~_x;

  ASSERT_EQ(~'a', not1('a'));
}
