// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/context.hpp"

#include "gtest/gtest.h"

TEST(context_test, identity_pass_trou_value) {
  ASSERT_EQ(5, Lel::Identity()(5));
  ASSERT_EQ(7, Lel::Identity()(7));
  ASSERT_EQ(-2, Lel::Identity()(-2));
}
