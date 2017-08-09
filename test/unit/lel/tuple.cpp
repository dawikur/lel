// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/tuple.hpp"

#include "gtest/gtest.h"

#include "lel_test.hpp"

TEST(tuple_test, with_single_non_empty_class_is_not_empty) {
  using Tuple = LeL::Tuple<NonEmpty>;

  ASSERT_FALSE(std::is_empty<Tuple>::value);
}

TEST(tuple_test, with_multiple_non_empty_classes_is_not_empty) {
  using Tuple = LeL::Tuple<NonEmpty, NonEmpty, NonEmpty>;

  ASSERT_FALSE(std::is_empty<Tuple>::value);
}

TEST(tuple_test, with_mix_of_empty_and_non_empty_is_not_empty) {
  using Tuple = LeL::Tuple<NonEmpty, Empty, Empty, NonEmpty>;

  ASSERT_FALSE(std::is_empty<Tuple>::value);
}

TEST(tuple_test, with_only_empty_class_is_empty) {
  using Tuple = LeL::Tuple<Empty, Empty>;

  ASSERT_TRUE(std::is_empty<Tuple>::value);
}
