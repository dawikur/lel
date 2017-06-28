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

template <class ViewLT, class ViewRT, class RawT, class ModeT>
struct Context {
  using ViewL = ViewLT;
  using ViewR = ViewRT;
  using Raw   = RawT;
  using Mode  = ModeT;
};

template <class Context, char ...ID>
struct Impl {
 public:
  constexpr explicit Impl() : left(), right() {}

  constexpr explicit Impl(typename Context::ViewL left)
    : left(std::move(left)), right() {}

  constexpr explicit Impl(typename Context::ViewL left,
                          typename Context::ViewR right)
    : left(std::move(left)), right(std::move(right)) {}

  template <class... Values>
  constexpr auto operator()(Values &&... values) const {
    return raw(typename Context::Mode(), std::forward<Values>(values)...);
  }

 private:
  template <class Value>
  constexpr auto raw(Single, Value &&value) const {
    return typename Context::Raw()(left(std::forward<Value>(value)));
  }

  template <class Value>
  constexpr auto raw(Left, Value &&value) const {
    return typename Context::Raw()(left(std::forward<Value>(value)), right);
  }

  template <class Value>
  constexpr auto raw(Right, Value &&value) const {
    return typename Context::Raw()(left, right(std::forward<Value>(value)));
  }

  template <class Value>
  constexpr auto raw(Both, Value &&value) const {
    return
      typename Context::Raw()(left(std::forward<Value>(value)), right(value));
  }

  template <class... Values>
  constexpr auto raw(Fold, Values &&... values) const {
    return typename Context::Raw()(std::forward<Values>(values)...);
  }

  typename Context::ViewL const left;
  typename Context::ViewR const right;
};

#define OPERATION(MARK, FUNC)                                                  \
  template <char... ID, class Rest, class Value>                               \
  constexpr auto operator MARK(Impl<Rest, ID...> view, Value value)            \
    ->Impl<Context<Impl<Rest, ID...>, Value, std::FUNC<>, Left>, ID...> {      \
    return Impl<Context<Impl<Rest, ID...>, Value, std::FUNC<>, Left>, ID...>(  \
      std::move(view), std::move(value));                                      \
  }                                                                            \
  template <char... ID, class Rest, class Value>                               \
  constexpr auto operator MARK(Value value, Impl<Rest, ID...> view)            \
    ->Impl<Context<Value, Impl<Rest, ID...>, std::FUNC<>, Right>, ID...> {     \
    return Impl<Context<Value, Impl<Rest, ID...>, std::FUNC<>, Right>, ID...>( \
      std::move(value), std::move(view));                                      \
  }                                                                            \
  template <char... ID, class RestL, class RestR>                              \
  constexpr auto operator MARK(Impl<RestL, ID...> viewL,                       \
                               Impl<RestR, ID...> viewR)                       \
    ->Impl<Context<Impl<RestL, ID...>, Impl<RestR, ID...>, std::FUNC<>, Both>, \
           ID...> {                                                            \
    return Impl<Context<Impl<RestL, ID...>,                                    \
                        Impl<RestR, ID...>,                                    \
                        std::FUNC<>,                                           \
                        Both>,                                                 \
                ID...>(std::move(viewL), std::move(viewR));                    \
  }                                                                            \
  template <char... IDL, class RestL, char... IDR, class RestR>                \
  constexpr auto operator MARK(Impl<RestL, IDL...> viewL,                      \
                               Impl<RestR, IDR...> viewR)                      \
    ->Impl<Context<Impl<RestL, IDL...>,                                        \
                   Impl<RestR, IDR...>,                                        \
                   std::FUNC<>,                                                \
                   Fold>,                                                      \
           '\0'> {                                                             \
    return Impl<Context<Impl<RestL, IDL...>,                                   \
                        Impl<RestR, IDR...>,                                   \
                        std::FUNC<>,                                           \
                        Fold>,                                                 \
                '\0'>(std::move(viewL), std::move(viewR));                     \
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
    return Impl<Context<Impl<Rest, ID...>, Identity, std::FUNC<>, Single>,     \
                ID...>(std::move(view));                                       \
  }

OPERATION( - , negate      );
OPERATION( ! , logical_not );
OPERATION( ~ , bit_not     );

#undef OPERATION

template <char ID>
using Placeholder = Impl<Context<Identity, Identity, Identity, Single>, ID>;

}  // namespace Seg

#endif  // INCLUDE_SEG_HPP_
