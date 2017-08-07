// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/lambda.hpp"

#include "gtest/gtest.h"

class lambda_test : public ::testing::Test {
 protected:
  using Empty = LeL::Lambda<LeL::Context<LeL::Identity>, LeL::Box<char>>;
};

TEST_F(lambda_test, pasthou_lambda_has_size_1) {
  ASSERT_EQ(1, sizeof(Empty));
}

TEST_F(lambda_test, pastthou_lambda_is_empty) {
  ASSERT_TRUE(std::is_empty<Empty>::value);
}
