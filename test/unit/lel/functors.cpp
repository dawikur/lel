// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/functors.hpp"

#include "gtest/gtest.h"

TEST(functors_test, indentity_can_be_used_in_constexpr) {
  static_assert(LeL::Identity()(true), "");
}

TEST(functors_test, identity_pass_trou_value) {
  ASSERT_EQ(5, LeL::Identity()(5));
  ASSERT_EQ(7, LeL::Identity()(7));
  ASSERT_EQ(-2, LeL::Identity()(-2));
}

TEST(functors_test, assign_will_set_value) {
  int val = 5;

  ASSERT_EQ(7, LeL::Assign()(val, 7));
  ASSERT_EQ(2, LeL::Assign()(val, 2));
}

TEST(functors_test, subscript_will_return_element_of_array) {
  int array[] = { 0, 1, 2, 3 };

  ASSERT_EQ(2, LeL::Subscript()(array, 2));
  ASSERT_EQ(1, LeL::Subscript()(array, 1));
}

TEST(functors_test, call_can_be_called_without_arguments) {
  ASSERT_EQ(3, LeL::Call()([]() { return 3; }));
}

TEST(functors_test, call_will_actually_call_left_operand) {
  ASSERT_EQ(4, LeL::Call()([](int i) { return i+3; }, 1));
}

TEST(functors_test, call_will_more_than_one_argument) {
  ASSERT_EQ(
    7, LeL::Call()([](int a, int b, int c) { return a + b + c; }, 4, 2, 1));
}
