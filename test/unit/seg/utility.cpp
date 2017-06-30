
#include "seg/utility.hpp"

#include "gtest/gtest.h"

TEST(utility_test, identity_pass_trou_value) {
  int value = 5;

  ASSERT_EQ(value, Seg::Identity()(value));
}
