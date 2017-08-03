// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel.hpp"

#include <memory>
#include <vector>

#include "gtest/gtest.h"

class single_lel_placeholder_test : public ::testing::Test {
 protected:
  LeL::Reference _;
  LeL::Placeholder<'x'> _x;
  LeL::Placeholder<'y'> _y;
};

TEST_F(single_lel_placeholder_test, assign_simple_value) {
  int value1 = 2;
  int value2 = 4;
  int value3 = 7;
  int value4 = 9;
  int value5 = 12;

  auto assign1 = (_(value1) = _x);
  auto assign2 = (_x = value2);
  auto assign3 = (_x = _y);

  assign1(3);
  assign2(value3);
  assign3(value4, value5);

  ASSERT_EQ(3, value1);
  ASSERT_EQ(4, value2);
  ASSERT_EQ(12, value4);
}

TEST_F(single_lel_placeholder_test, subscription_on_array) {
  auto value = _x[3];

  int array[5] = {2, 4, 5, 7, 3};

  ASSERT_EQ(array[3], value(array));
}

TEST_F(single_lel_placeholder_test, subscriptino_on_vector) {
  auto value = _x[4];

  std::vector<int> vec{0, 3, 6, 9, 12, 15};

  ASSERT_EQ(vec[4], value(vec));
}

TEST_F(single_lel_placeholder_test, shift_left) {
  auto value1 = _x << 2;
  auto value2 = 1 << _x;

  ASSERT_EQ(8, value1(2));
  ASSERT_EQ(4, value2(2));
}

TEST_F(single_lel_placeholder_test, shift_right) {
  auto value1 = _x >> 2;
  auto value2 = 7 >> _x;

  ASSERT_EQ(2, value1(8));
  ASSERT_EQ(1, value2(2));
}


TEST_F(single_lel_placeholder_test, indirection_on_pointer) {
  auto get = *_x;

  int value = 5;

  ASSERT_EQ(5, get(&value));
}

TEST_F(single_lel_placeholder_test, indirection_of_unique_ptr) {
  auto get = *_x;

  auto ptr = std::make_unique<int>(5);

  ASSERT_EQ(5, get(ptr));
}

TEST_F(single_lel_placeholder_test, address_of) {
  auto addr = &_x;

  int value = 5;

  ASSERT_EQ(&value, addr(value));
}

TEST_F(single_lel_placeholder_test, address_of_unique_ptr) {
  auto addr = &_x;

  auto ptr = std::make_unique<int>(5);

  ASSERT_EQ(&ptr, addr(ptr));
}

TEST_F(single_lel_placeholder_test, plus_assignment) {
  int value1 = 4;
  int value2 = 7;
  int value3 = 9;
  int value4 = 8;
  int value5 = 6;

  auto assign1 = value1 += _x;
  auto assign2 = _x += value2;
  auto assign3 = _x += _y;

  assign1(2);
  assign2(value3);
  assign3(value4, value5);

  ASSERT_EQ(6, value1);
  ASSERT_EQ(16, value3);
  ASSERT_EQ(14, value4);
}

TEST_F(single_lel_placeholder_test, minus_assignment) {
  int value1 = 4;
  int value2 = 7;
  int value3 = 9;
  int value4 = 8;
  int value5 = 6;

  auto assign1 = value1 -= _x;
  auto assign2 = _x -= value2;
  auto assign3 = _x -= _y;

  assign1(2);
  assign2(value3);
  assign3(value4, value5);

  ASSERT_EQ(2, value1);
  ASSERT_EQ(2, value3);
  ASSERT_EQ(2, value4);
}

TEST_F(single_lel_placeholder_test, multiply_assignment) {
  int value1 = 4;
  int value2 = 7;
  int value3 = 9;
  int value4 = 8;
  int value5 = 6;

  auto assign1 = value1 *= _x;
  auto assign2 = _x *= value2;
  auto assign3 = _x *= _y;

  assign1(2);
  assign2(value3);
  assign3(value4, value5);

  ASSERT_EQ(8, value1);
  ASSERT_EQ(63, value3);
  ASSERT_EQ(48, value4);
}

struct Object {
  int value;
};

TEST_F(single_lel_placeholder_test, pointer_to_member) {
  Object obj1 =  {9};
  Object obj2 = {11};
  Object obj3 = {13};

  auto call1 = (&obj1)->*_y;
  auto call2 = _x->*(&Object::value);
  auto call3 = _x->*_y;

  ASSERT_EQ( 9, call1(&Object::value));
  ASSERT_EQ(11, call2(&obj2));
  ASSERT_EQ(13, call3(&obj3, &Object::value));
}

TEST_F(single_lel_placeholder_test, pre_increment) {
  auto inc = ++_x;

  int value = 5;

  ASSERT_EQ(6, inc(value));
  ASSERT_EQ(6, value);
}

TEST_F(single_lel_placeholder_test, post_increment) {
  auto inc = _x++;

  int value = 5;

  ASSERT_EQ(5, inc(value));
  ASSERT_EQ(6, value);
}

TEST_F(single_lel_placeholder_test, pre_decrement) {
  auto inc = --_x;

  int value = 5;

  ASSERT_EQ(4, inc(value));
  ASSERT_EQ(4, value);
}

TEST_F(single_lel_placeholder_test, post_decrement) {
  auto inc = _x--;

  int value = 5;

  ASSERT_EQ(5, inc(value));
  ASSERT_EQ(4, value);
}

TEST_F(single_lel_placeholder_test, can_be_used_with_non_copyable) {
  auto print = std::cout << _x;

  print("use cout to test\n");
}
