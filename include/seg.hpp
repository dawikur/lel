// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_SEG_HPP_
#define INCLUDE_SEG_HPP_

#include <functional>
#include <type_traits>

namespace Seg {

struct Identity {
  template <class Type>
  constexpr auto operator()(Type const &value) const {
    return value;
  }
};

struct Single {};
struct Left {};
struct Right {};
struct Both {};
struct Fold {};

template <class ViewLT, class ViewRT, class FuncT, class ModeT>
struct Context {
  using ViewL = ViewLT;
  using ViewR = ViewRT;
  using Func  = FuncT;
  using Mode  = ModeT;
};

template <class Context, char ...ID>
struct Impl {
 public:
  constexpr Impl() : left(), right() {}

  constexpr Impl(typename Context::ViewL left, typename Context::ViewR right)
    : left(std::move(left)), right(std::move(right)) {}

  template <class... Values>
  constexpr auto operator()(Values &&... values) const {
    return call(typename Context::Mode(), std::forward<Values>(values)...);
  }

 private:
  template <class Value>
  constexpr auto call(Single, Value &&value) const {
    return typename Context::Func()(left(std::forward<Value>(value)));
  }

  template <class Value>
  constexpr auto call(Left, Value &&value) const {
    return typename Context::Func()(left(std::forward<Value>(value)), right);
  }

  template <class Value>
  constexpr auto call(Right, Value &&value) const {
    return typename Context::Func()(left, right(std::forward<Value>(value)));
  }

  template <class Value>
  constexpr auto call(Both, Value &&value) const {
    return
      typename Context::Func()(left(std::forward<Value>(value)), right(value));
  }

  template <class... Values>
  constexpr auto call(Fold, Values &&... values) const {
    // TODO: 2017-06-29: slice;
    // values should be split into two sections and passed to left and right
    // Than Fold could be merged with Both
    return typename Context::Func()(std::forward<Values>(values)...);
  }

  typename Context::ViewL const left;
  typename Context::ViewR const right;
};

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

template <char ID>
using Placeholder = Impl<Context<Identity, Identity, Identity, Single>, ID>;

}  // namespace Seg

#endif  // INCLUDE_SEG_HPP_
