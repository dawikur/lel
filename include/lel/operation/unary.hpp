// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_OPERATION_UNARY_HPP_
#define INCLUDE_LEL_OPERATION_UNARY_HPP_

#include <functional>

#include "lel/lambda.hpp"

namespace LeL {

#define OPERATION_STD(MARK, FUNC) OPERATION(MARK, std::FUNC<>)
#define OPERATION_LEL(MARK, FUNC)                                              \
  namespace Operation {                                                        \
  struct __##FUNC {                                                            \
    template <class Value>                                                     \
    constexpr decltype(auto) operator()(Value &&value) const {                 \
      return (MARK std::forward<Value>(value));                                \
    }                                                                          \
  };                                                                           \
  }                                                                            \
  OPERATION(MARK, Operation::__##FUNC)

#define OPERATION(MARK, FUNC)                                                  \
  template <class Rest, class IDs>                                             \
  constexpr decltype(auto) operator MARK(Lambda<Rest, IDs> view) {             \
    return Lambda<Unary<Lambda<Rest, IDs>, FUNC>, IDs>{std::move(view)};       \
  }

OPERATION_STD( - , negate      )
OPERATION_STD( ! , logical_not )
OPERATION_STD( ~ , bit_not     )

OPERATION    ( + , Identity    )

OPERATION_LEL( * , Indirection )
OPERATION_LEL( & , AddressOf   )

#undef OPERATION
#undef OPERATION_LEL
#undef OPERATION_STD

}  // namespace LeL

#endif  // INCLUDE_LEL_OPERATION_UNARY_HPP_
