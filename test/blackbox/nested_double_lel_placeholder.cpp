// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel.hpp"

#include "gtest/gtest.h"

class nested_double_lel_placeholder_test : public ::testing::Test {
 protected:
  Lel::Placeholder<'1'> _1;
  Lel::Placeholder<'2'> _2;
  Lel::Placeholder<'x'> _x;
  Lel::Placeholder<'y'> _y;
};

TEST_F(nested_double_lel_placeholder_test, two_unique_pointers) {
  auto sum = *((*_x)[1]) + **(_y[2]);

  auto x = std::make_unique<std::vector<std::unique_ptr<int>>>();
  x->push_back(std::make_unique<int>(1));
  x->push_back(std::make_unique<int>(2));
  x->push_back(std::make_unique<int>(3));
  x->push_back(std::make_unique<int>(4));

  auto y = std::vector<std::unique_ptr<std::unique_ptr<int>>>();
  y.push_back(std::make_unique<std::unique_ptr<int>>(std::make_unique<int>(6)));
  y.push_back(std::make_unique<std::unique_ptr<int>>(std::make_unique<int>(7)));
  y.push_back(std::make_unique<std::unique_ptr<int>>(std::make_unique<int>(8)));
  y.push_back(std::make_unique<std::unique_ptr<int>>(std::make_unique<int>(9)));

  ASSERT_EQ(2+8, sum(x, y));
}

TEST_F(nested_double_lel_placeholder_test, index_two_unique_pointers) {
  auto sum = *((*_x)[_1]) + **(_y[_2]);

  auto x = std::make_unique<std::vector<std::unique_ptr<int>>>();
  x->push_back(std::make_unique<int>(1));
  x->push_back(std::make_unique<int>(2));
  x->push_back(std::make_unique<int>(3));
  x->push_back(std::make_unique<int>(4));

  auto y = std::vector<std::unique_ptr<std::unique_ptr<int>>>();
  y.push_back(std::make_unique<std::unique_ptr<int>>(std::make_unique<int>(6)));
  y.push_back(std::make_unique<std::unique_ptr<int>>(std::make_unique<int>(7)));
  y.push_back(std::make_unique<std::unique_ptr<int>>(std::make_unique<int>(8)));
  y.push_back(std::make_unique<std::unique_ptr<int>>(std::make_unique<int>(9)));

  ASSERT_EQ(4+7, sum(3, 1, x, y));
}
