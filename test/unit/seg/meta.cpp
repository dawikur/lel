// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "seg.hpp"

#include "gtest/gtest.h"

TEST(meta_test, identity_returns_same_object) {
  ASSERT_TRUE(Seg::Identity()(true));
  ASSERT_EQ(8, Seg::Identity()(8));
}

