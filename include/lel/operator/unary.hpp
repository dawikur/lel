// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_OPERATOR_UNARY_HPP_
#define INCLUDE_LEL_OPERATOR_UNARY_HPP_

#include <functional>

#include "lel/lambda.hpp"

namespace LeL {

#define OPERATOR_STD(MARK, FUNC) OPERATOR(MARK, std::FUNC<>)
#define OPERATOR_LEL(MARK, FUNC)                                               \
  namespace Operator {                                                         \
  struct FUNC {                                                                \
    template <class Value>                                                     \
    constexpr decltype(auto) operator()(Value &&value) const {                 \
      return (MARK std::forward<Value>(value));                                \
    }                                                                          \
  };                                                                           \
  }                                                                            \
  OPERATOR(MARK, Operator::FUNC)

#define OPERATOR(MARK, FUNC)                                                   \
  template <class Rest, class IDs>                                             \
  constexpr decltype(auto) operator MARK(Lambda<Rest, IDs> view) {             \
    return Lambda<Context<FUNC, Lambda<Rest, IDs>>, IDs>{std::move(view)};     \
  }

OPERATOR_STD( - , negate             )
OPERATOR_STD( ! , logical_not        )
OPERATOR_STD( ~ , bit_not            )

OPERATOR    ( + , Operator::Identity )

OPERATOR_LEL( * , Indirection        )
OPERATOR_LEL( & , AddressOf          )

#undef OPERATOR
#undef OPERATOR_LEL
#undef OPERATOR_STD

}  // namespace LeL

#endif  // INCLUDE_LEL_OPERATOR_UNARY_HPP_
