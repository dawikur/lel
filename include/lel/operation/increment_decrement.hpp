// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_OPERATION_INCREMENT_DECREMENT_HPP_
#define INCLUDE_LEL_OPERATION_INCREMENT_DECREMENT_HPP_

#include "lel/lambda.hpp"

namespace LeL {

#define OPERATION(MARK, FUNC, PRE, POST, INT)                                  \
  namespace Operation {                                                        \
  struct __##FUNC {                                                            \
    template <class Value>                                                     \
    constexpr decltype(auto) operator()(Value &&value) const {                 \
      return (PRE value POST);                                                 \
    }                                                                          \
  };                                                                           \
  }                                                                            \
  template <class Rest, class IDs>                                             \
  constexpr decltype(auto) operator MARK(Lambda<Rest, IDs> view INT) {         \
    return Lambda<Context<Operation::__##FUNC, Lambda<Rest, IDs>>, IDs>{       \
      std::move(view)};                                                        \
  }

#define INT , int

OPERATION( ++ , PreIncrement  , ++ ,     ,     )
OPERATION( ++ , PostIncrement ,    , ++  , INT )
OPERATION( -- , PreDecrement  , -- ,     ,     )
OPERATION( -- , PostDecrement ,    , --  , INT )

#undef INT
#undef OPERATION

}  // namespace LeL

#endif  // INCLUDE_LEL_OPERATION_INCREMENT_DECREMENT_HPP_
