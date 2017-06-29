// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_SEG_IMPL_HPP_
#define INCLUDE_SEG_IMPL_HPP_

#include <utility>

#include "seg/utility.hpp"

namespace Seg {

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
      typename Context::Func()(left(value), right(value));
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

}  // namespace Seg

#endif  // INCLUDE_SEG_IMPL_HPP_
