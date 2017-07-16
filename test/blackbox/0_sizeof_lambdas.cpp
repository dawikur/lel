// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel.hpp"

#include "gtest/gtest.h"

class sizeof_lambdas_test : public ::testing::Test {
 protected:
  LeL::Placeholder<'x'> _x;
  LeL::Placeholder<'y'> _y;
};

TEST_F(sizeof_lambdas_test, base_placeholder_is_1) {
  ASSERT_EQ(1, sizeof(_x));
}

TEST_F(sizeof_lambdas_test, DISABLED_placeholder_with_one_int_equals_size_of_int) {
  ASSERT_EQ(sizeof(1), sizeof(_x + 1));
}

TEST_F(sizeof_lambdas_test, DISABLED_placeholder_with_two_ints_equals_sizof_to_ints) {
  ASSERT_EQ(sizeof(1) + sizeof(5), sizeof(_x + 1 < 5));
}

TEST_F(sizeof_lambdas_test, DISABLED_multiple_base_placehlder_is_1) {
  ASSERT_EQ(1, sizeof(_x < _y));
}
