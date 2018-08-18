// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/template/sequence.hpp"

#include "gtest/gtest.h"

#include "lel_test.hpp"

class sequence_test : public ::testing::Test {
 protected:
  template <int... Values>
  using Sequence = LeL::Template::Sequence<int, Values...>;

  template <std::size_t Num, std::size_t Size = Num>
  using MakeSequence = LeL::Template::MakeSequence<Num, Size>;
};

TEST_F(sequence_test, index_of_can_be_used_in_constexpr) {
  static_assert(Sequence<1, 3, 4, 7, 9, 10>::IndexOf<9>() == 4, "");
}

TEST_F(sequence_test, index_of_first_value) {
  ASSERT_EQ(0, (Sequence<2, 4, 6>::IndexOf<2>()));
}

TEST_F(sequence_test, index_of_not_first_value) {
  ASSERT_EQ(4, (Sequence<1, 3, 4, 7, 9, 10>::IndexOf<9>()));
}

TEST_F(sequence_test, back_of_one_element_sequence_returns_this_element) {
  ASSERT_EQ(5, (Sequence<5>::Back()));
}

TEST_F(sequence_test, back_of_sequence_returns_last_element) {
  ASSERT_EQ(5, (Sequence<1, 2, 3, 4, 5>::Back()));
}

TEST_F(sequence_test, pop_front_id_removes_first_item_if_true) {
  ASSERT_TYPE((Sequence<2, 4>()), (Sequence<1, 2, 4>::PopFrontIf<true>()));
}

TEST_F(sequence_test, pop_front_id_removes_first_item_if_false) {
  ASSERT_TYPE((Sequence<1, 2, 4>()), (Sequence<1, 2, 4>::PopFrontIf<false>()));
}

TEST_F(sequence_test, make_sequence_with_one_value) {
  ASSERT_TYPE((std::index_sequence<0>()), (MakeSequence<1>()));
}

TEST_F(sequence_test, make_sequence_with_two_same_values) {
  ASSERT_TYPE((std::index_sequence<0, 1, 2>()), (MakeSequence<3, 3>()));
}

TEST_F(sequence_test, make_sequence_with_size_less_than_number) {
  ASSERT_TYPE((std::index_sequence<0, 1, 2, 3, 4>()), (MakeSequence<5, 3>()));
}

TEST_F(sequence_test, make_sequence_with_size_greater_than_number) {
  ASSERT_TYPE((std::index_sequence<0, 1, 2, 2, 2>()), (MakeSequence<3, 5>()));
}
