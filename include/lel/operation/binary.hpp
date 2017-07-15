// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_OPERATION_BINARY_HPP_
#define INCLUDE_LEL_OPERATION_BINARY_HPP_

#include <functional>

#include "lel/lambda.hpp"

namespace LeL {

// TODO: 2017-07-04
// , ??

#define OPERATION_STD(MARK, FUNC) OPERATION(MARK, std::FUNC<>)
#define OPERATION_LEL(MARK, FUNC)                                              \
  namespace Operation {                                                        \
  struct __##FUNC {                                                            \
    template <class Left, class Right>                                         \
    constexpr decltype(auto) operator()(Left &&left, Right &&right) const {    \
      return (std::forward<Left>(left) MARK std::forward<Right>(right));       \
    }                                                                          \
  };                                                                           \
  }                                                                            \
  OPERATION(MARK, Operation::__##FUNC)

#define OPERATION(MARK, FUNC)                                                  \
  template <class Rest, class IDs, class Value>                                \
  constexpr decltype(auto) operator MARK(Lambda<Rest, IDs> view,               \
                                         Value &&value) {                      \
    return Lambda<Context<FUNC, Lambda<Rest, IDs>, Wrap<Value>>, IDs>{         \
      std::move(view), std::forward<Value>(value)};                            \
  }                                                                            \
  template <class Value, class Rest, class IDs>                                \
  constexpr decltype(auto) operator MARK(Value &&value,                        \
                                         Lambda<Rest, IDs> view) {             \
    return Lambda<Context<FUNC, Wrap<Value>, Lambda<Rest, IDs>>, IDs>{         \
      std::forward<Value>(value), std::move(view)};                            \
  }                                                                            \
  template <class RestL, class IDL, class RestR, class IDR>                    \
  constexpr decltype(auto) operator MARK(Lambda<RestL, IDL> viewL,             \
                                         Lambda<RestR, IDR> viewR) {           \
    return Lambda<Context<FUNC, Lambda<RestL, IDL>, Lambda<RestR, IDR>>,       \
                  Merge<IDL, IDR>>{std::move(viewL), std::move(viewR)};        \
  }

OPERATION_STD( +   , plus             )
OPERATION_STD( -   , minus            )
OPERATION_STD( *   , multiplies       )
OPERATION_STD( /   , divides          )
OPERATION_STD( %   , modulus          )

OPERATION_STD( ==  , equal_to         )
OPERATION_STD( !=  , not_equal_to     )
OPERATION_STD( >   , greater          )
OPERATION_STD( <   , less             )
OPERATION_STD( >=  , greater_equal    )
OPERATION_STD( <=  , less_equal       )

OPERATION_STD( &&  , logical_and      )
OPERATION_STD( ||  , logical_or       )

OPERATION_STD( &   , bit_and          )
OPERATION_STD( |   , bit_or           )
OPERATION_STD( ^   , bit_xor          )

OPERATION_LEL( <<  , ShiftLeft        )
OPERATION_LEL( >>  , ShiftRight       )

OPERATION_LEL( +=  , PlusAssign       )
OPERATION_LEL( -=  , MinusAssign      )
OPERATION_LEL( *=  , MulAssign        )
OPERATION_LEL( /=  , DivAssign        )
OPERATION_LEL( %=  , ModAssign        )

OPERATION_LEL( &=  , AndAssign        )
OPERATION_LEL( |=  , OrAssign         )
OPERATION_LEL( ^=  , XorAssign        )

OPERATION_LEL( <<= , ShiftLeftAssign  )
OPERATION_LEL( >>= , ShiftRightAssign )

OPERATION_LEL( ->* , PointerToMember  )

#undef OPERATION
#undef OPERATION_LEL
#undef OPERATION_STD

}  // namespace LeL

#endif  // INCLUDE_LEL_OPERATION_BINARY_HPP_
