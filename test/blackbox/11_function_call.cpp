// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel.hpp"

#include "gtest/gtest.h"

int free_func(int val) {
  return val + 2;
}

TEST(function_call_test, works_with_lambda) {
  LeL::Placeholder<'x'> _x;
  LeL::Placeholder<'y'> _y;
  LeL::Reference<char> _;

  auto add_one = _x + 1;

  auto call_with = _x._(_y);
  auto pass_five = _x._(5);
  auto add_two = _(add_one)._(_x) + 1;
  auto add_values = add_one + _y;

  ASSERT_EQ(3, call_with(add_one, 2));
  ASSERT_EQ(6, pass_five(add_one));
  ASSERT_EQ(4, add_two(2));
  ASSERT_EQ(8, add_values(3, 4));
}

TEST(function_call_test, works_with_free_function) {
  LeL::Placeholder<'x'> _x;
  LeL::Placeholder<'y'> _y;
  LeL::Reference<char> _;

  auto call_with = _x._(_y);
  auto pass_five = _x._(5);
  auto add_three = _(free_func)._(_x) + 1;

  ASSERT_EQ(4, call_with(free_func, 2));
  ASSERT_EQ(7, pass_five(free_func));
  ASSERT_EQ(9, add_three(6));
}

TEST(function_call_test, works_with_static_methods) {
  struct Foo {
    static int Bar(int val) {
      return val + 2;
    }
  };

  LeL::Placeholder<'x'> _x;
  LeL::Placeholder<'y'> _y;
  LeL::Reference<char> _;

  auto call_with = _x._(_y);
  auto pass_five = _x._(5);
  auto add_three = _(Foo::Bar)._(_x) + 1;

  ASSERT_EQ(4, call_with(Foo::Bar, 2));
  ASSERT_EQ(7, pass_five(Foo::Bar));
  ASSERT_EQ(9, add_three(6));
}

TEST(function_call_test, works_with_core_lambda) {
  LeL::Placeholder<'x'> _x;
  LeL::Placeholder<'y'> _y;
  LeL::Reference<char> _;

  auto call_with = _x._(_y);
  auto pass_five = _x._(5);
  auto add_three = _([](int i) { return i+2; })._(_x) + 1;

  ASSERT_EQ(4, call_with([](int i) { return i+2; }, 2));
  ASSERT_EQ(7, pass_five([](int i) { return i+2; }));
  ASSERT_EQ(9, add_three(6));
}

