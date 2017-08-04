// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#include "lel/variadic.hpp"

#include "gtest/gtest.h"

#include "lel_test.hpp"

namespace {

template <class ...>
struct List {};

struct Empty{};
struct NonEmpty{ int v; };

template <class Type>
using PredBase = std::is_same<Type, int>;

template <class Type>
using PredStruct = std::is_empty<Type>;

}  // namespace

TEST(variadic_test, variadic_get_can_be_used_in_constexpr) {
  static_assert(LeL::Variadic::Get<0>::Value(11, 22, 33, 44, 55) == 11, "");
  static_assert(LeL::Variadic::Get<1>::Value(11, 22, 33, 44, 55) == 22, "");
  static_assert(LeL::Variadic::Get<2>::Value(11, 22, 53, 46, 55) == 53, "");
  static_assert(LeL::Variadic::Get<3>::Value(11, 22, 33, 46, 55) == 46, "");
}

TEST(variadic_test, variadic_get_returns_proper_value) {
  ASSERT_EQ(11, LeL::Variadic::Get<0>::Value(11, 22, 33, 44, 55));
  ASSERT_EQ(22, LeL::Variadic::Get<1>::Value(11, 22, 33, 44, 55));
  ASSERT_EQ(53, LeL::Variadic::Get<2>::Value(11, 22, 53, 46, 55));
  ASSERT_EQ(46, LeL::Variadic::Get<3>::Value(11, 22, 33, 46, 55));
}

TEST(variadic_test, variadic_get_returns_proper_type) {
  ASSERT_TYPE(int(),     (LeL::Variadic::Get<0>::Type<int, char, bool, int64_t>()));
  ASSERT_TYPE(char(),    (LeL::Variadic::Get<1>::Type<int, char, bool, int64_t>()));
  ASSERT_TYPE(bool(),    (LeL::Variadic::Get<2>::Type<int, char, bool, int64_t>()));
  ASSERT_TYPE(int64_t(), (LeL::Variadic::Get<3>::Type<int, char, bool, int64_t>()));
}

TEST(variadic_test, variadic_filter_of_basic_types) {
  using Input = List<int, bool, int, int64_t>;
  using Output = List<bool, int64_t>;

  using Result = LeL::Variadic::From<Input>::RemoveIf<PredBase>;

  ASSERT_TYPE(Output(), Result());
}

TEST(variadic_test, variadic_filter_of_structs) {
  using Input = List<Empty, Empty, NonEmpty, Empty, NonEmpty>;
  using Output = List<NonEmpty, NonEmpty>;

  using Result = LeL::Variadic::From<Input>::RemoveIf<PredStruct>;

  ASSERT_TYPE(Output(), Result());
}
