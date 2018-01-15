// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/template/box.hpp"

#include "gtest/gtest.h"

#include "lel_test.hpp"

class box_test : public ::testing::Test {
 protected:
  template <int... Values>
  using Box = LeL::Template::Box<std::less<>, int, Values...>;

  template <int... Values>
  using BoxGe = LeL::Template::Box<std::greater<>, int, Values...>;
};

TEST_F(box_test, indexes_of_returns_empty_list_on_empty_input) {
  ASSERT_TYPE((Box<>()), (Box<1, 2, 3, 4>::IndexesOf<>()));
}

TEST_F(box_test, indexes_returns_one_element_for_one_input) {
  ASSERT_TYPE((Box<2>()), (Box<3, 8, 9>::IndexesOf<9>()));
}

TEST_F(box_test, indexes_return_multiple_values) {
  ASSERT_TYPE((Box<2, 4>()), (Box<3, 8, 9, 12, 15>::IndexesOf<9, 15>()));
}

TEST_F(box_test, non_empty_merge_empty_gives_non_empty) {
  ASSERT_TYPE((Box<1, 2>()), (LeL::Template::Merge<Box<1, 2>, Box<>>()));
}

TEST_F(box_test, empty_merge_non_empty_gives_non_empty) {
  ASSERT_TYPE((Box<4, 8>()), (LeL::Template::Merge<Box<>, Box<4, 8>>()));
}

TEST_F(box_test, merge_two_sequnces_of_one_element) {
  ASSERT_TYPE((Box<1, 4>()), (LeL::Template::Merge<Box<1>, Box<4>>()));
  ASSERT_TYPE((Box<1, 4>()), (LeL::Template::Merge<Box<4>, Box<1>>()));
}

TEST_F(box_test, non_empty_merge_with_bigger_separable_non_empty) {
  ASSERT_TYPE((Box<1, 4, 8, 9>()),
              (LeL::Template::Merge<Box<1, 4>, Box<8, 9>>()));
}

TEST_F(box_test, merge_unique_intersecting) {
  ASSERT_TYPE((Box<1, 2, 3, 4, 5>()),
              (LeL::Template::Merge<Box<1, 3>, Box<2, 4, 5>>()));
}

TEST_F(box_test, non_empty_merge_with_intersecting_non_empty) {
  ASSERT_TYPE((Box<1, 4, 9, 11>()),
              (LeL::Template::Merge<Box<1, 4, 9>, Box<9, 11>>()));
}

TEST_F(box_test, merge_will_remove_duplicate_enties) {
  ASSERT_TYPE((Box<4, 8, 9, 11>()),
              (LeL::Template::Merge<Box<4, 8, 9>, Box<8, 9, 11>>()));
}

TEST_F(box_test, merge_boxes_with_same_tails) {
  ASSERT_TYPE((Box<1, 4, 8, 9>()),
              (LeL::Template::Merge<Box<4, 8, 9>, Box<1, 8, 9>>()));
}

TEST_F(box_test, merge_same_boxes) {
  ASSERT_TYPE((Box<1, 3, 7>()),
              (LeL::Template::Merge<Box<1, 3, 7>, Box<1, 3, 7>>()));
}

TEST_F(box_test, merge_with_same_subsequences) {
  ASSERT_TYPE((Box<1, 3, 5, 7, 9>()),
              (LeL::Template::Merge<Box<1, 5, 7>, Box<3, 5, 7, 9>>()));
}

TEST_F(box_test, greater_order_non_empty_merge_empty_gives_non_empty) {
  ASSERT_TYPE((BoxGe<2, 1>()), (LeL::Template::Merge<BoxGe<2, 1>, BoxGe<>>()));
}

TEST_F(box_test, greater_order_empty_merge_non_empty_gives_non_empty) {
  ASSERT_TYPE((BoxGe<8, 4>()), (LeL::Template::Merge<BoxGe<>, BoxGe<8, 4>>()));
}

TEST_F(box_test, greater_order_merge_two_sequnces_of_one_element) {
  ASSERT_TYPE((BoxGe<4, 1>()), (LeL::Template::Merge<BoxGe<1>, BoxGe<4>>()));
  ASSERT_TYPE((BoxGe<4, 1>()), (LeL::Template::Merge<BoxGe<4>, BoxGe<1>>()));
}

TEST_F(box_test,
       greater_order_non_empty_merge_with_bigger_separable_non_empty) {
  ASSERT_TYPE((BoxGe<9, 8, 4, 1>()),
              (LeL::Template::Merge<BoxGe<4, 1>, BoxGe<9, 8>>()));
}

TEST_F(box_test, merge_unique_greater_order_intersecting) {
  ASSERT_TYPE((BoxGe<5, 4, 3, 2, 1>()),
              (LeL::Template::Merge<BoxGe<3, 1>, BoxGe<5, 4, 2>>()));
}

TEST_F(box_test, greater_order_non_empty_merge_with_intersecting_non_empty) {
  ASSERT_TYPE((BoxGe<11, 9, 4, 1>()),
              (LeL::Template::Merge<BoxGe<9, 4, 1>, BoxGe<11, 9>>()));
}

TEST_F(box_test, greater_order_merge_will_remove_duplicate_enties) {
  ASSERT_TYPE((BoxGe<11, 9, 8, 4>()),
              (LeL::Template::Merge<BoxGe<9, 8, 4>, BoxGe<11, 9, 8>>()));
}

TEST_F(box_test, greater_order_merge_boxes_with_same_tails) {
  ASSERT_TYPE((BoxGe<9, 8, 4, 1>()),
              (LeL::Template::Merge<BoxGe<9, 8, 4>, BoxGe<9, 8, 1>>()));
}

TEST_F(box_test, greater_order_merge_same_boxes) {
  ASSERT_TYPE((BoxGe<7, 3, 1>()),
              (LeL::Template::Merge<BoxGe<7, 3, 1>, BoxGe<7, 3, 1>>()));
}

TEST_F(box_test, greater_order_merge_with_same_subsequences) {
  ASSERT_TYPE((BoxGe<9, 7, 5, 3, 1>()),
              (LeL::Template::Merge<BoxGe<7, 5, 1>, BoxGe<9, 7, 5, 3>>()));
}

