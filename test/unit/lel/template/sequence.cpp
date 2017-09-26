// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/template/sequence.hpp"

#include "gtest/gtest.h"

#include "lel_test.hpp"

TEST(sequence_test, zero_lenght_returns_empty_sequence) {
  ASSERT_TYPE(std::make_index_sequence<0>(),
              (LeL::Template::MakeSequence<0>()));
}

TEST(sequence_test, return_empty_sequence_if_there_is_nothing_to_fill) {
  ASSERT_TYPE(std::make_index_sequence<0>(),
              (LeL::Template::MakeSequence<0, 1>()));
}

TEST(sequence_test, with_one_parameter_output_is_same_as_make_index) {
  ASSERT_TYPE(std::make_index_sequence<5>(), LeL::Template::MakeSequence<5>());

  ASSERT_TYPE(std::make_index_sequence<7>(),
              (LeL::Template::MakeSequence<7, 7>()));
}

TEST(sequence_test, when_count_is_lower_than_max_pull_up_to_max) {
  ASSERT_TYPE(std::make_index_sequence<8>(),
              (LeL::Template::MakeSequence<8, 5>()));

  ASSERT_TYPE(std::make_index_sequence<9>(),
              (LeL::Template::MakeSequence<9, 4>()));
}

TEST(sequence_test, when_count_is_higher_than_max_fill_with_max_to_count) {
  ASSERT_TYPE((std::index_sequence<0, 1, 2, 3, 4, 4, 4>()),
              (LeL::Template::MakeSequence<5, 7>()));

  ASSERT_TYPE((std::index_sequence<0, 1, 2, 2, 2, 2, 2, 2>()),
              (LeL::Template::MakeSequence<3, 8>()));
}
