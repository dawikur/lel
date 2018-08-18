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
};

TEST_F(pointer_to_member_test, returns_field_of_a_struct) {
  Struct s{8};

  auto value_from_struct = &_x->*(&Struct::value);
  auto field_from_struct = &_x->*_y;
  auto field = &s->*_y;

  ASSERT_EQ(8, value_from_struct(s));
  ASSERT_EQ(8, field_from_struct(s, &Struct::value));
  ASSERT_EQ(8, field(&Struct::value));
}
