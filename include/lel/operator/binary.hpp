// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_OPERATOR_BINARY_HPP_
#define INCLUDE_LEL_OPERATOR_BINARY_HPP_

#include <functional>

#include "lel/lambda.hpp"

namespace LeL {

#define OPERATOR_STD(MARK, FUNC) OPERATOR(MARK, std::FUNC<>)
#define OPERATOR_LEL(MARK, FUNC)                                               \
  namespace Operator {                                                         \
  struct __##FUNC {                                                            \
    template <class Left, class Right>                                         \
    constexpr decltype(auto) operator()(Left &&left, Right &&right) const {    \
      return (std::forward<Left>(left) MARK std::forward<Right>(right));       \
    }                                                                          \
  };                                                                           \
  }                                                                            \
  OPERATOR(MARK, Operator::__##FUNC)

#define OPERATOR(MARK, FUNC)                                                   \
  template <class Rest, class IDs, class Value>                                \
  constexpr decltype(auto) operator MARK(Lambda<Rest, IDs> view,               \
                                         Value &&          value) {            \
    return Lambda<Context<FUNC, Lambda<Rest, IDs>, Wrap<Value const>>, IDs>{   \
      std::move(view), std::forward<Value>(value)};                            \
  }                                                                            \
  template <class Value, class Rest, class IDs>                                \
  constexpr decltype(auto) operator MARK(Value &&          value,              \
                                         Lambda<Rest, IDs> view) {             \
    return Lambda<Context<FUNC, Wrap<Value const>, Lambda<Rest, IDs>>, IDs>{   \
      std::forward<Value>(value), std::move(view)};                            \
  }                                                                            \
  template <class RestL, class IDL, class RestR, class IDR>                    \
  constexpr decltype(auto) operator MARK(Lambda<RestL, IDL> viewL,             \
                                         Lambda<RestR, IDR> viewR) {           \
    return Lambda<Context<FUNC, Lambda<RestL, IDL>, Lambda<RestR, IDR>>,       \
                  Template::Merge<IDL, IDR>>{std::move(viewL),                 \
                                             std::move(viewR)};                \
  }

OPERATOR_STD( +   , plus             )
OPERATOR_STD( -   , minus            )
OPERATOR_STD( *   , multiplies       )
OPERATOR_STD( /   , divides          )
OPERATOR_STD( %   , modulus          )

OPERATOR_STD( ==  , equal_to         )
OPERATOR_STD( !=  , not_equal_to     )
OPERATOR_STD( >   , greater          )
OPERATOR_STD( <   , less             )
OPERATOR_STD( >=  , greater_equal    )
OPERATOR_STD( <=  , less_equal       )

OPERATOR_STD( &&  , logical_and      )
OPERATOR_STD( ||  , logical_or       )

OPERATOR_STD( &   , bit_and          )
OPERATOR_STD( |   , bit_or           )
OPERATOR_STD( ^   , bit_xor          )

OPERATOR_LEL( <<  , ShiftLeft        )
OPERATOR_LEL( >>  , ShiftRight       )

OPERATOR_LEL( +=  , PlusAssign       )
OPERATOR_LEL( -=  , MinusAssign      )
OPERATOR_LEL( *=  , MulAssign        )
OPERATOR_LEL( /=  , DivAssign        )
OPERATOR_LEL( %=  , ModAssign        )

OPERATOR_LEL( &=  , AndAssign        )
OPERATOR_LEL( |=  , OrAssign         )
OPERATOR_LEL( ^=  , XorAssign        )

OPERATOR_LEL( <<= , ShiftLeftAssign  )
OPERATOR_LEL( >>= , ShiftRightAssign )

OPERATOR_LEL( ->* , PointerToMember  )

#undef OPERATOR
#undef OPERATOR_LEL
#undef OPERATOR_STD

}  // namespace LeL

#endif  // INCLUDE_LEL_OPERATOR_BINARY_HPP_
