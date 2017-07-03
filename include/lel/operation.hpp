// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_OPERATION_HPP_
#define INCLUDE_LEL_OPERATION_HPP_

#include <functional>

#include "lel/impl.hpp"

namespace Lel {

#define OPERATION_STD(MARK, FUNC) OPERATION(MARK, std::FUNC<>)
#define OPERATION_LEL(MARK, FUNC)                                              \
  struct __##FUNC {                                                            \
    template <class Left, class Right>                                         \
    constexpr auto operator()(Left &&left, Right &&right) const {              \
      return std::forward<Left>(left) MARK std::forward<Right>(right);         \
    }                                                                          \
  };                                                                           \
  OPERATION(MARK, __##FUNC)

#define OPERATION(MARK, FUNC)                                                  \
  template <class Rest, class IDs, class Value>                                \
  constexpr auto operator MARK(Impl<Rest, IDs> view, Value value)              \
    ->Impl<Context<Impl<Rest, IDs>, Value, FUNC, Left>, IDs> {                 \
    return {std::move(view), std::move(value)};                                \
  }                                                                            \
  template <class Rest, class IDs, class Value>                                \
  constexpr auto operator MARK(Value value, Impl<Rest, IDs> view)              \
    ->Impl<Context<Value, Impl<Rest, IDs>, FUNC, Right>, IDs> {                \
    return {std::move(value), std::move(view)};                                \
  }                                                                            \
  template <class RestL, class RestR, class IDs>                               \
  constexpr auto operator MARK(Impl<RestL, IDs> viewL, Impl<RestR, IDs> viewR) \
    ->Impl<Context<Impl<RestL, IDs>, Impl<RestR, IDs>, FUNC, Both>, IDs> {     \
    return {std::move(viewL), std::move(viewR)};                               \
  }                                                                            \
  template <class RestL, class IDL, class RestR, class IDR>                    \
  constexpr auto operator MARK(Impl<RestL, IDL> viewL, Impl<RestR, IDR> viewR) \
    ->Impl<Context<Impl<RestL, IDL>, Impl<RestR, IDR>, FUNC, Fold>,            \
           Merge<IDL, IDR>> {                                                  \
    return {std::move(viewL), std::move(viewR)};                               \
  }

OPERATION_STD( +  , plus          );
OPERATION_STD( -  , minus         );
OPERATION_STD( *  , multiplies    );
OPERATION_STD( /  , divides       );
OPERATION_STD( %  , modulus       );

OPERATION_STD( == , equal_to      );
OPERATION_STD( != , not_equal_to  );
OPERATION_STD( >  , greater       );
OPERATION_STD( <  , less          );
OPERATION_STD( >= , greater_equal );
OPERATION_STD( <= , less_equal    );

OPERATION_STD( && , logical_and   );
OPERATION_STD( || , logical_or    );

OPERATION_STD( &  , bit_and       );
OPERATION_STD( |  , bit_or        );
OPERATION_STD( ^  , bit_xor       );

OPERATION_LEL( << , ShiftLeft     );
OPERATION_LEL( >> , ShiftRight    );

// =
// += -=
// *= /= %/
// <<= >>=
// &= ^= |=

// , ??

#undef OPERATION
#undef OPERATION_LEL

#define OPERATION(MARK, FUNC)                                                  \
  template <class Rest, class IDs>                                             \
  constexpr auto operator MARK(Impl<Rest, IDs> view)                           \
    ->Impl<Context<Impl<Rest, IDs>, Identity, FUNC, Single>, IDs> {            \
    return {std::move(view), Identity{}};                                      \
  }

// ++/-- postfix increment/decrement
// ++/+--prefix increment/decrement

// * indirection
// & address of
// sizeof

OPERATION_STD( - , negate      );
OPERATION_STD( ! , logical_not );
OPERATION_STD( ~ , bit_not     );

OPERATION( + , Identity );

#undef OPERATION

#undef OPERATION_STD

}  // namespace Lel

#endif  // INCLUDE_LEL_OPERATION_HPP_
