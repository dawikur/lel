// Copyright 2018, Dawid Kurek, <dawikur@gmail.com>

#include <memory>
#include <vector>

#include <assert.h>

#include "lel.hpp"

int main() {
  ///
  using namespace lel;

  // simple
  auto plus_one = _x + 1;
  auto multiply = _x * _y;
  auto is_less  = _1 < _2;

  assert(plus_one(2) == 3);
  assert(multiply(2, 3) == 6);
  assert(is_less(2, 5));

  // more arguments
  auto compute_something = 1 + _x * 3 - _y * _y + _x * _z;

  compute_something(1, 2, 3);

  // own placeholders
  auto first_arg  = lel::placeholder<'1'>();
  auto second_arg = lel::placeholder<'2'>();

  auto not_equal = first_arg != second_arg;

  assert(not_equal(2, 3));

  // more complex
  auto add_of_vectors = *((*_x)[_1]) + **(_y[_2]);

  auto x_vec = std::make_unique<std::vector<std::unique_ptr<int>>>();
  x_vec->push_back(std::make_unique<int>(1));
  x_vec->push_back(std::make_unique<int>(2));
  x_vec->push_back(std::make_unique<int>(3));
  x_vec->push_back(std::make_unique<int>(4));

  auto y_vec = std::vector<std::unique_ptr<std::unique_ptr<int>>>();
  y_vec.push_back(std::make_unique<std::unique_ptr<int>>(std::make_unique<int>(6)));
  y_vec.push_back(std::make_unique<std::unique_ptr<int>>(std::make_unique<int>(7)));
  y_vec.push_back(std::make_unique<std::unique_ptr<int>>(std::make_unique<int>(8)));
  y_vec.push_back(std::make_unique<std::unique_ptr<int>>(std::make_unique<int>(9)));

  assert((4+7) == (add_of_vectors(3, 1, x_vec, y_vec)));

  // references
  int x = 5;

  auto add_to_x = _(x) += _y;

  add_to_x(8);

  assert(x == 13);

  // currying
  auto sum = _x + _y + _z;

  sum(1, 2, 3);
  sum(1)(2, 3);
  sum(1, 2)(3);
  sum(1)(2)(3);

  // function call
  auto call_with = _x._(_y);
  call_with(printf, "call with\n");

  auto do_with_str = _x._("do with string\n");
  do_with_str(printf);

  auto print = _(printf)._(_y);
  print("print\n");

  auto format = _(printf)._(_1, _2, _3, _4, _5, _6);
  format("format %s with %s %d %d %s", "string", "argument", 1, 2, "\n");

  ///
}
