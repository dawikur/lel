// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/operator/increment_decrement.hpp"

#include "gtest/gtest.h"

TEST(increment_decrement_test, preincrement) {
  LeL::Operator::PreIncrement pre_increment;

  int i = 5;

  ASSERT_EQ(6, pre_increment(i));
}

TEST(increment_decrement_test, postincrement) {
  LeL::Operator::PostIncrement post_increment;

  int i = 5;

  ASSERT_EQ(5, post_increment(i));
}

TEST(increment_decrement_test, predecrement) {
  LeL::Operator::PreDecrement pre_decrement;

  int i = 5;

  ASSERT_EQ(4, pre_decrement(i));
}

TEST(increment_decrement_test, postdecrement) {
  LeL::Operator::PostDecrement post_decrement;

  int i = 5;

  ASSERT_EQ(5, post_decrement(i));
}
