// Copyright 2018, Dawid Kurek, <dawikur@gmail.com>

#include <memory>
#include <vector>

#include <assert.h>

#include "lel.hpp"

int main() {
  /// BEGIN
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

  assert(3 == compute_something(1, 2, 3));

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

  assert(6 == sum(1, 2, 3));
  assert(6 == sum(1)(2, 3));
  assert(6 == sum(1, 2)(3));
  assert(6 == sum(1)(2)(3));

  // function call
  auto duplicate = [](int i) {
    return i * 2;
  };

  auto call_with = _x._(_y);
  assert(8 == call_with(duplicate, 4));

  auto do_with_three = _x._(3);
  assert(6 == do_with_three(duplicate));

  auto times_two = _(duplicate)._(_y);
  assert(10 == times_two(5));

  auto agregate = [](int a, int b, int c, int d) {
    return a + b + c + d;
  };

  auto reduce = _(agregate)._(_a, _b, _c, _d);
  assert(20 == reduce(2, 4, 6, 8));

  //
  struct Object {
    Object(int value) : value(value) {}

    int Method(int arg) { return value * arg; }

    int value;
  };

  Object object(5);

  // struct field
  auto get_value = (&_x->*_y);
  auto set_value = get_value = _z;

  set_value(object, &Object::value, 8);
  assert(get_value(object, &Object::value) == 8);

  // method call
  auto call_method = get_value._(_z);

  assert(call_method(object, &Object::Method, 3) == 24);

  /// END
}
