// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_SEG_OPERATION_HPP_
#define INCLUDE_SEG_OPERATION_HPP_

#include <functional>

#include "seg/impl.hpp"

namespace Seg {

#define OPERATION(MARK, FUNC)                                                  \
  template <class Rest, class IDs, class Value>                                \
  constexpr auto operator MARK(Impl<Rest, IDs> view, Value value)              \
    ->Impl<Context<Impl<Rest, IDs>, Value, std::FUNC<>, Left>, IDs> {          \
    return {std::move(view), std::move(value)};                                \
  }                                                                            \
  template <class Rest, class IDs, class Value>                                \
  constexpr auto operator MARK(Value value, Impl<Rest, IDs> view)              \
    ->Impl<Context<Value, Impl<Rest, IDs>, std::FUNC<>, Right>, IDs> {         \
    return {std::move(value), std::move(view)};                                \
  }                                                                            \
  template <class RestL, class RestR, class IDs>                               \
  constexpr auto operator MARK(Impl<RestL, IDs> viewL, Impl<RestR, IDs> viewR) \
    ->Impl<Context<Impl<RestL, IDs>, Impl<RestR, IDs>, std::FUNC<>, Both>,     \
           IDs> {                                                              \
    return {std::move(viewL), std::move(viewR)};                               \
  }                                                                            \
  template <class RestL, class IDL, class RestR, class IDR>                    \
  constexpr auto operator MARK(Impl<RestL, IDL> viewL, Impl<RestR, IDR> viewR) \
    ->Impl<Context<Impl<RestL, IDL>, Impl<RestR, IDR>, std::FUNC<>, Fold>,     \
           Merge<IDL, IDR>> {                                                  \
    return {std::move(viewL), std::move(viewR)};                               \
  }

OPERATION( +  , plus          );
OPERATION( -  , minus         );
OPERATION( *  , multiplies    );
OPERATION( /  , divides       );
OPERATION( %  , modulus       );

OPERATION( == , equal_to      );
OPERATION( != , not_equal_to  );
OPERATION( >  , greater       );
OPERATION( <  , less          );
OPERATION( >= , greater_equal );
OPERATION( <= , less_equal    );

OPERATION( && , logical_and   );
OPERATION( || , logical_or    );

OPERATION( &  , bit_and       );
OPERATION( |  , bit_or        );
OPERATION( ^  , bit_xor       );

#undef OPERATION

#define OPERATION(MARK, FUNC)                                                  \
  template <class Rest, class IDs>                                             \
  constexpr auto operator MARK(Impl<Rest, IDs> view)                           \
    ->Impl<Context<Impl<Rest, IDs>, Identity, std::FUNC<>, Single>, IDs> {     \
    return {std::move(view), Identity{}};                                      \
  }

OPERATION( - , negate      );
OPERATION( ! , logical_not );
OPERATION( ~ , bit_not     );

#undef OPERATION

}  // namespace Seg

#endif  // INCLUDE_SEG_OPERATION_HPP_
