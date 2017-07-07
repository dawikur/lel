// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/context.hpp"

#include "gtest/gtest.h"

TEST(context_test, identity_pass_trou_value) {
  ASSERT_EQ(5, LeL::Identity()(5));
  ASSERT_EQ(7, LeL::Identity()(7));
  ASSERT_EQ(-2, LeL::Identity()(-2));
}

TEST(context_test, TODO) {
  LeL::Assign ass;
  LeL::Subscript sub;
  (void)ass;
  (void)sub;
}
