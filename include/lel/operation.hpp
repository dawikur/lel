// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_OPERATION_HPP_
#define INCLUDE_LEL_OPERATION_HPP_

#include <functional>

#include "lel/impl.hpp"

namespace LeL {

#define OPERATION_STD(MARK, FUNC) OPERATION(MARK, std::FUNC<>)

#define OPERATION_LEL(MARK, FUNC)                                              \
  struct __##FUNC {                                                            \
    template <class Left, class Right>                                         \
    constexpr decltype(auto) operator()(Left &&left, Right &&right) const {    \
      return std::forward<Left>(left) MARK std::forward<Right>(right);         \
    }                                                                          \
  };                                                                           \
  OPERATION(MARK, __##FUNC)

#define OPERATION(MARK, FUNC)                                                  \
  template <class Rest, class IDs, class Value>                                \
  constexpr decltype(auto) operator MARK(Impl<Rest, IDs> view, Value value) {  \
    return Impl<Context<Impl<Rest, IDs>, Value, FUNC, Left>, IDs>{             \
      std::move(view), std::move(value)};                                      \
  }                                                                            \
  template <class Rest, class IDs, class Value>                                \
  constexpr decltype(auto) operator MARK(Value value, Impl<Rest, IDs> view) {  \
    return Impl<Context<Value, Impl<Rest, IDs>, FUNC, Right>, IDs>{            \
      std::move(value), std::move(view)};                                      \
  }                                                                            \
  template <class RestL, class IDL, class RestR, class IDR>                    \
  constexpr decltype(auto) operator MARK(Impl<RestL, IDL> viewL,               \
                                         Impl<RestR, IDR> viewR) {             \
    return Impl<Context<Impl<RestL, IDL>, Impl<RestR, IDR>, FUNC, Fold>,       \
                Merge<IDL, IDR>>{std::move(viewL), std::move(viewR)};          \
  }

OPERATION_STD( +  , plus              )
OPERATION_STD( -  , minus             )
OPERATION_STD( *  , multiplies        )
OPERATION_STD( /  , divides           )
OPERATION_STD( %  , modulus           )

OPERATION_STD( == , equal_to          )
OPERATION_STD( != , not_equal_to      )
OPERATION_STD( >  , greater           )
OPERATION_STD( <  , less              )
OPERATION_STD( >= , greater_equal     )
OPERATION_STD( <= , less_equal        )

OPERATION_STD( && , logical_and       )
OPERATION_STD( || , logical_or        )

OPERATION_STD( &  , bit_and           )
OPERATION_STD( |  , bit_or            )
OPERATION_STD( ^  , bit_xor           )

OPERATION_LEL( << , ShiftLeft         )
OPERATION_LEL( >> , ShiftRight        )

OPERATION_LEL( += , PlusAssign        )
OPERATION_LEL( -= , MinusAssign       )
OPERATION_LEL( *= , MulAssign         )
OPERATION_LEL( /= , DivAssign         )
OPERATION_LEL( %= , ModAssign         )

OPERATION_LEL( &= , AndAssign         )
OPERATION_LEL( |= , OrAssign          )
OPERATION_LEL( ^= , XorAssign         )

OPERATION_LEL( <<= , ShiftLeftAssign  )
OPERATION_LEL( >>= , ShiftRightAssign )

// TODO: 2017-07-04
// , ??

#undef OPERATION
#undef OPERATION_LEL

#define OPERATION_LEL(MARK, FUNC)                                              \
  struct __##FUNC {                                                            \
    template <class Value>                                                     \
    constexpr decltype(auto) operator()(Value &&value) const {                 \
      return MARK std::forward<Value>(value);                                  \
    }                                                                          \
  };                                                                           \
  OPERATION(MARK, __##FUNC)

#define OPERATION(MARK, FUNC)                                                  \
  template <class Rest, class IDs>                                             \
  constexpr decltype(auto) operator MARK(Impl<Rest, IDs> view) {               \
    return Impl<Context<Impl<Rest, IDs>, Identity, FUNC, Single>, IDs>{        \
      std::move(view), Identity{}};                                            \
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

#define OPERATION(FUNC, PRE, POST)                                             \
  struct __##FUNC {                                                            \
    template <class Value>                                                     \
    constexpr decltype(auto) operator()(Value &&value) const {                 \
      return PRE std::forward<Value>(value) POST;                              \
    }                                                                          \
  };

OPERATION( PreIncrement  , ++ ,    )
OPERATION( PostIncrement ,    , ++ )
OPERATION( PreDecrement  , -- ,    )
OPERATION( PostDecrement ,    , -- )

#undef OPERATION

template <class Rest, class IDs>
constexpr decltype(auto) operator++(Impl<Rest, IDs> view) {
  return Impl<Context<Impl<Rest, IDs>, Identity, __PreIncrement, Single>, IDs>{
    std::move(view), Identity{}};
}

template <class Rest, class IDs>
constexpr decltype(auto) operator++(Impl<Rest, IDs> view, int) {
  return Impl<Context<Impl<Rest, IDs>, Identity, __PostIncrement, Single>, IDs>{
    std::move(view), Identity{}};
}

template <class Rest, class IDs>
constexpr decltype(auto) operator--(Impl<Rest, IDs> view) {
  return Impl<Context<Impl<Rest, IDs>, Identity, __PreDecrement, Single>, IDs>{
    std::move(view), Identity{}};
}

template <class Rest, class IDs>
constexpr decltype(auto) operator--(Impl<Rest, IDs> view, int) {
  return Impl<Context<Impl<Rest, IDs>, Identity, __PostDecrement, Single>, IDs>{
    std::move(view), Identity{}};
}

}  // namespace LeL

#endif  // INCLUDE_LEL_OPERATION_HPP_
