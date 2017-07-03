// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/variadic.hpp"

#include "gtest/gtest.h"

TEST(variadic_test, variadic_get_returns_proper_value) {
  ASSERT_EQ(11, Lel::Variadic().Get<0>(11, 22, 33, 44, 55));
  ASSERT_EQ(22, Lel::Variadic().Get<1>(11, 22, 33, 44, 55));
  ASSERT_EQ(53, Lel::Variadic().Get<2>(11, 22, 53, 46, 55));
  ASSERT_EQ(46, Lel::Variadic().Get<3>(11, 22, 33, 46, 55));
}
