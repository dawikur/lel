// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_SEG_IMPL_HPP_
#define INCLUDE_SEG_IMPL_HPP_

#include <utility>

#include "seg/context.hpp"
#include "seg/variadic.hpp"

namespace Seg {

template <class Context, class IDs>
struct Impl;

template <class Context, char... IDs>
struct Impl<Context, Box<char, IDs...>> {
 public:
  constexpr Impl() : left(), right() {}

  constexpr Impl(typename Context::ViewL left, typename Context::ViewR right)
    : left(std::move(left)), right(std::move(right)) {}

  template <class... Values>
  constexpr auto operator()(Values &&... values) const {
    return call(typename Context::Mode(), std::forward<Values>(values)...);
  }

  // () function call
  // [] subscript
  // . -> member access
  // .* ->* pointer to member

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
    return typename Context::Func()(left(Variadic().Get<0>(value)),
                                    right(Variadic().Get<0>(value)));
  }

  template <class... Values>
  constexpr auto call(Fold, Values &&... values) const {
    return typename Context::Func()(left.slice(Box<char, IDs...>(), values...),
                                    right.slice(Box<char, IDs...>(), values...));
  }

  template <char... Slice, class... Values>
  constexpr auto slice(Box<char, Slice...>, Values &&... values) const {
    using Indexes = typename Box<char, Slice...>::template IndexesOf<IDs...>;

    return slice(Indexes(), std::forward<Values>(values)...);
  }

  template <int... Indexes, class... Values>
  constexpr auto slice(Box<int, Indexes...>, Values &&... values) const {
    return call(typename Context::Mode(),
                Variadic().Get<Indexes>(values...)...);
  }

  typename Context::ViewL const left;
  typename Context::ViewR const right;

  template <class ContextF, class IDsF>
  friend struct Impl;
};

}  // namespace Seg

#endif  // INCLUDE_SEG_IMPL_HPP_
