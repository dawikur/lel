// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_SEG_OPERATION_HPP_
#define INCLUDE_SEG_OPERATION_HPP_

#include <functional>

#include "seg/impl.hpp"

namespace Seg {

#define STD(FUNC) std::FUNC<>

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

OPERATION( +  , STD(plus)          );
OPERATION( -  , STD(minus)         );
OPERATION( *  , STD(multiplies)    );
OPERATION( /  , STD(divides)       );
OPERATION( %  , STD(modulus)       );

OPERATION( == , STD(equal_to)      );
OPERATION( != , STD(not_equal_to)  );
OPERATION( >  , STD(greater)       );
OPERATION( <  , STD(less)          );
OPERATION( >= , STD(greater_equal) );
OPERATION( <= , STD(less_equal)    );

OPERATION( && , STD(logical_and)   );
OPERATION( || , STD(logical_or)    );

OPERATION( &  , STD(bit_and)       );
OPERATION( |  , STD(bit_or)        );
OPERATION( ^  , STD(bit_xor)       );

#undef OPERATION

// ++/-- postfix increment/decrement
// () function call
// [] subscript
// . -> member access

// ++/+--prefix increment/decrement
// * indirection
// & address of
// sizeof

// .* ->* pointer to member

// << >> bitwise left shft and right shift

// =
// += -=
// *= /= %/
// <<= >>=
// &= ^= |=
//
// , ??

#define OPERATION(MARK, FUNC)                                                  \
  template <class Rest, class IDs>                                             \
  constexpr auto operator MARK(Impl<Rest, IDs> view)                           \
    ->Impl<Context<Impl<Rest, IDs>, Identity, FUNC, Single>, IDs> {            \
    return {std::move(view), Identity{}};                                      \
  }

OPERATION( + , Identity );

OPERATION( - , STD(negate)      );
OPERATION( ! , STD(logical_not) );
OPERATION( ~ , STD(bit_not)     );

#undef OPERATION

#undef STD

}  // namespace Seg

#endif  // INCLUDE_SEG_OPERATION_HPP_
