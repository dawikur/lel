// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "seg/context.hpp"

#include "gtest/gtest.h"

TEST(context_test, identity_pass_trou_value) {
  ASSERT_EQ(5, Seg::Identity()(5));
  ASSERT_EQ(7, Seg::Identity()(7));
  ASSERT_EQ(-2, Seg::Identity()(-2));
}
