// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/context.hpp"

#include "gtest/gtest.h"

TEST(context_test, indentity_can_be_used_in_constexpr) {
  static_assert(LeL::Identity()(true), "");
}

TEST(context_test, identity_pass_trou_value) {
  ASSERT_EQ(5, LeL::Identity()(5));
  ASSERT_EQ(7, LeL::Identity()(7));
  ASSERT_EQ(-2, LeL::Identity()(-2));
}

TEST(context_test, assign_will_set_value) {
  int val = 5;

  ASSERT_EQ(7, LeL::Assign()(val, 7));
  ASSERT_EQ(2, LeL::Assign()(val, 2));
}

TEST(context_test, subscript_will_return_element_of_array) {
  int array[] = { 0, 1, 2, 3 };

  ASSERT_EQ(2, LeL::Subscript()(array, 2));
  ASSERT_EQ(1, LeL::Subscript()(array, 1));
}
