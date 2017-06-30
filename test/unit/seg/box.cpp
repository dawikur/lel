// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "seg/box.hpp"

#include "gtest/gtest.h"

#include "seg_test.hpp"

class box_test : public ::testing::Test {
 protected:
  using NonEmpty = Seg::Box<int, 1, 4, 6, 2>;
  using Empty    = Seg::Box<int>;
};

TEST_F(box_test, non_empty_merge_empty_gives_non_empty) {
  ASSERT_TYPE(NonEmpty, (Seg::Merge<NonEmpty, Empty>()));
}

TEST_F(box_test, empty_merge_non_empty_gives_non_empty) {
  ASSERT_TYPE(NonEmpty, (Seg::Merge<Empty, NonEmpty>()));
}
