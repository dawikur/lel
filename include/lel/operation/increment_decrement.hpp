// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_OPERATION_INCREMENT_DECREMENT_HPP_
#define INCLUDE_LEL_OPERATION_INCREMENT_DECREMENT_HPP_

#include "lel/impl.hpp"

namespace LeL {

#define OPERATION(MARK, FUNC, PRE, POST, INT)                                  \
  namespace Operation {                                                        \
  struct __##FUNC {                                                            \
    template <class Value>                                                     \
    constexpr decltype(auto) operator()(Value &&value) const {                 \
      return PRE std::forward<Value>(value) POST;                              \
    }                                                                          \
  };                                                                           \
  }                                                                            \
  template <class Rest, class IDs>                                             \
  constexpr decltype(auto) operator MARK(Impl<Rest, IDs> view INT) {           \
    return Impl<Context<Impl<Rest, IDs>,                                       \
                        Identity,                                              \
                        Operation::__##FUNC,                                   \
                        Single>,                                               \
                IDs>{std::move(view), Identity{}};                             \
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
