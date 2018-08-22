// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_OPERATOR_INCREMENT_DECREMENT_HPP_
#define INCLUDE_LEL_OPERATOR_INCREMENT_DECREMENT_HPP_

#include "lel/lambda.hpp"

namespace LeL {

#define OPERATOR(MARK, FUNC, PRE, POST, INT)                                   \
  namespace Operator {                                                         \
  struct __##FUNC {                                                            \
    template <class Value>                                                     \
    constexpr decltype(auto) operator()(Value &&value) const {                 \
      return (PRE value POST);                                                 \
    }                                                                          \
  };                                                                           \
  }                                                                            \
  template <class Rest, class IDs>                                             \
  constexpr decltype(auto) operator MARK(Lambda<Rest, IDs> view INT) {         \
    return Lambda<Context<Operator::__##FUNC, Lambda<Rest, IDs>>, IDs>{        \
      std::move(view)};                                                        \
  }

#define INT , int

OPERATOR( ++ , PreIncrement  , ++ ,     ,     )
OPERATOR( ++ , PostIncrement ,    , ++  , INT )
OPERATOR( -- , PreDecrement  , -- ,     ,     )
OPERATOR( -- , PostDecrement ,    , --  , INT )

#undef INT
#undef OPERATOR

}  // namespace LeL

#endif  // INCLUDE_LEL_OPERATOR_INCREMENT_DECREMENT_HPP_
