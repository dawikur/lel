// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "seg/context.hpp"

#include "gtest/gtest.h"

TEST(context_test, identity_pass_trou_value) {
  int value = 5;

  ASSERT_EQ(value, Seg::Identity()(value));
}
