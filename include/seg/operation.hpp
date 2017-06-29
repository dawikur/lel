// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_SEG_OPERATION_HPP_
#define INCLUDE_SEG_OPERATION_HPP_

#include <functional>

#include "seg/impl.hpp"

namespace Seg {

#define OPERATION(MARK, FUNC)                                                  \
  template <char... ID, class Rest, class Value>                               \
  constexpr auto operator MARK(Impl<Rest, ID...> view, Value value)            \
    ->Impl<Context<Impl<Rest, ID...>, Value, std::FUNC<>, Left>, ID...> {      \
      return {std::move(view), std::move(value)};                              \
  }                                                                            \
  template <char... ID, class Rest, class Value>                               \
  constexpr auto operator MARK(Value value, Impl<Rest, ID...> view)            \
    ->Impl<Context<Value, Impl<Rest, ID...>, std::FUNC<>, Right>, ID...> {     \
      return {std::move(value), std::move(view)};                              \
  }                                                                            \
  template <char... ID, class RestL, class RestR>                              \
  constexpr auto operator MARK(Impl<RestL, ID...> viewL,                       \
                               Impl<RestR, ID...> viewR)                       \
    ->Impl<Context<Impl<RestL, ID...>, Impl<RestR, ID...>, std::FUNC<>, Both>, \
           ID...> {                                                            \
      return {std::move(viewL), std::move(viewR)};                             \
  }                                                                            \
  template <char... IDL, class RestL, char... IDR, class RestR>                \
  constexpr auto operator MARK(Impl<RestL, IDL...> viewL,                      \
                               Impl<RestR, IDR...> viewR)                      \
    ->Impl<Context<Impl<RestL, IDL...>,                                        \
                   Impl<RestR, IDR...>,                                        \
                   std::FUNC<>,                                                \
                   Fold>,                                                      \
           IDL..., IDR...> {                                                   \
      return {std::move(viewL), std::move(viewR)};                             \
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
  template <char... ID, class Rest>                                            \
  constexpr auto operator MARK(Impl<Rest, ID...> view)                         \
    ->Impl<Context<Impl<Rest, ID...>, Identity, std::FUNC<>, Single>, ID...> { \
      return {std::move(view), Identity{}};                                    \
  }

OPERATION( - , negate      );
OPERATION( ! , logical_not );
OPERATION( ~ , bit_not     );

#undef OPERATION

}  // namespace Seg

#endif  // INCLUDE_SEG_OPERATION_HPP_
