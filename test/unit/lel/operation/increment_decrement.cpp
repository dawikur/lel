// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/operation/increment_decrement.hpp"

#include "gtest/gtest.h"

TEST(increment_decrement_test, preincrement) {
  LeL::Operation::__PreIncrement pre_increment;

  int i = 5;

  ASSERT_EQ(6, pre_increment(i));
}

TEST(increment_decrement_test, postincrement) {
  LeL::Operation::__PostIncrement post_increment;

  int i = 5;

  ASSERT_EQ(5, post_increment(i));
}

TEST(increment_decrement_test, predecrement) {
  LeL::Operation::__PreDecrement pre_decrement;

  int i = 5;

  ASSERT_EQ(4, pre_decrement(i));
}

TEST(increment_decrement_test, postdecrement) {
  LeL::Operation::__PostDecrement post_decrement;

  int i = 5;

  ASSERT_EQ(5, post_decrement(i));
}
