
#include <memory>
#include <vector>

#include <assert.h>

#include "lel.hpp"

int main() {
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
  call_with(printf, "str");

  auto do_with_str = _x._("str");
  do_with_str(printf);

  auto print = _(printf)._(_y);
  print("str");

  auto format = _(printf)._(_1, _2, _3);
  format("sample %s with %d", "string", 5);
}
