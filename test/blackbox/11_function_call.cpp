// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel.hpp"

#include "gtest/gtest.h"

class function_call_test : public ::testing::Test {
 protected:
  LeL::Placeholder<'x'> _x;
  LeL::Placeholder<'y'> _y;
  LeL::Reference<char> _;
};

int free_func(int val) {
  return val + 2;
}

TEST_F(function_call_test, works_with_lambda) {
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

TEST_F(function_call_test, works_with_free_function) {
  auto call_with = _x._(_y);
  auto pass_five = _x._(5);
  auto add_three = _(free_func)._(_x) + 1;

  ASSERT_EQ(4, call_with(free_func, 2));
  ASSERT_EQ(7, pass_five(free_func));
  ASSERT_EQ(9, add_three(6));
}

TEST_F(function_call_test, works_with_static_methods) {
  struct Foo {
    static int Bar(int val) {
      return val + 2;
    }
  };

  auto call_with = _x._(_y);
  auto pass_five = _x._(5);
  auto add_three = _(Foo::Bar)._(_x) + 1;

  ASSERT_EQ(4, call_with(Foo::Bar, 2));
  ASSERT_EQ(7, pass_five(Foo::Bar));
  ASSERT_EQ(9, add_three(6));
}

TEST_F(function_call_test, works_with_core_lambda) {
  auto call_with = _x._(_y);
  auto pass_five = _x._(5);
  auto add_three = _([](int i) { return i+2; })._(_x) + 1;

  ASSERT_EQ(4, call_with([](int i) { return i+2; }, 2));
  ASSERT_EQ(7, pass_five([](int i) { return i+2; }));
  ASSERT_EQ(9, add_three(6));
}

TEST_F(function_call_test, works_with_operator_call_from_object) {
  struct Callable {
    int operator()(int i) { return 3 + i; }
  } callable;

  auto call = _x._(_y);

  ASSERT_EQ(7, call(callable, 4));
}

TEST_F(function_call_test, works_with_zero_argument_function) {
  struct Callable {
    int operator()() { return 3; }
  } callable;

  auto call = _x._();

  ASSERT_EQ(3, call(callable));
}

TEST_F(function_call_test, works_with_multiple_number_of_parameters) {
  struct Callable {
    int operator()(int, int) { return 2; }
    int operator()(int, int, int) { return 3; }
  } callable;

  auto count2 = _(callable)._(_x, _y);
  auto count3 = _(callable)._(_x, _x, _x);

  ASSERT_EQ(2, count2(1, 2));
  ASSERT_EQ(3, count3(1));
}

TEST_F(function_call_test, works_with_variadic_number_of_parameters) {

}
