// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/variadic.hpp"

#include "gtest/gtest.h"

#include "lel_test.hpp"

TEST(variadic_test, variadic_get_returns_proper_value) {
  ASSERT_EQ(11, LeL::Variadic::Get<0>::Value(11, 22, 33, 44, 55));
  ASSERT_EQ(22, LeL::Variadic::Get<1>::Value(11, 22, 33, 44, 55));
  ASSERT_EQ(53, LeL::Variadic::Get<2>::Value(11, 22, 53, 46, 55));
  ASSERT_EQ(46, LeL::Variadic::Get<3>::Value(11, 22, 33, 46, 55));
}

TEST(variadic_test, variadic_get_returns_proper_type) {
  ASSERT_TYPE(int(),  (LeL::Variadic::Get<0>::Type<int, char, bool, long>()));
  ASSERT_TYPE(char(), (LeL::Variadic::Get<1>::Type<int, char, bool, long>()));
  ASSERT_TYPE(bool(), (LeL::Variadic::Get<2>::Type<int, char, bool, long>()));
  ASSERT_TYPE(long(), (LeL::Variadic::Get<3>::Type<int, char, bool, long>()));
}
