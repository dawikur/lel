// Copyright 2018, Dawid Kurek, <dawikur@gmail.com>

#include "lel.hpp"

#include "gtest/gtest.h"

class pointer_to_member_test : public ::testing::Test {
 protected:
  lel::reference _;
  lel::placeholder<'x'> _x;
  lel::placeholder<'y'> _y;
  lel::placeholder<'z'> _z;
};

struct Struct {
  int value;

  int Method(int i) {
    return i * value;
  }
};

TEST_F(pointer_to_member_test, returns_field_of_a_struct) {
  Struct s{8};

  auto value_from_struct = &_x->*(&Struct::value);
  auto field_from_struct = &_x->*_y;
  auto field = &s->*_y;

  ASSERT_EQ(8, value_from_struct(s));
  ASSERT_EQ(8, field_from_struct(s, &Struct::value));
  ASSERT_EQ(8, field_from_struct(s)(&Struct::value));
  ASSERT_EQ(8, field(&Struct::value));
}

TEST_F(pointer_to_member_test, calls_method_of_an_object) {
  Struct s{7};

  auto call_method_of_an_struct = (&_x ->* _y)._(_z);
  auto call_method = (&s ->* _y)._(_z);
  auto call_object_with = (&_x ->* &Struct::Method)._(_z);

  ASSERT_EQ(21, call_method_of_an_struct(s, &Struct::Method, 3));
  ASSERT_EQ(14, call_method(&Struct::Method, 2));
  ASSERT_EQ(28, call_object_with(s, 4));
}
