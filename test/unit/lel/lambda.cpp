// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/lambda.hpp"

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <iostream>

using namespace ::testing;

class lambda_test : public ::testing::Test {
 protected:
  struct MockImpl {
    MOCK_CONST_METHOD0(slice0, int());
    MOCK_CONST_METHOD1(slice1, int(int));
  };

  template <class FuncT, FuncT Func>
  struct MockView {
    MockImpl& operator()() const {
      static MockImpl impl;
      return impl;
    }

    template <class Slice, class ... Args>
    auto slice(Slice, Args... args) const {
      return (operator()().*Func)(args...);
    }
  };
};

#define MOCK(ID, ARGS) \
  MockView<decltype(&MockImpl::slice##ID), &MockImpl::slice##ID> mock; \
  EXPECT_CALL(mock(), slice##ID(ARGS))

TEST_F(lambda_test, when_no_ids_and_view_doesnt_have_arguments_view_is_called) {
  MOCK(0, )
    .WillOnce(Return(5));

  LeL::Lambda<LeL::Context<LeL::Identity, decltype(mock)>,
              LeL::Template::Box<char>>
    lambda(mock);

  ASSERT_EQ(5, lambda());
}

TEST_F(lambda_test, when_no_ids_view_can_be_called_with_arguments) {
  MOCK(1, 1)
    .WillOnce(Return(7));

  LeL::Lambda<LeL::Context<LeL::Identity, decltype(mock)>,
              LeL::Template::Box<char, '0'>>
    lambda(mock);

  auto result = lambda(1);
  ASSERT_EQ(7, result);
}

#undef MOCK
