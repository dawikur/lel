// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_CONTEXT_HPP_
#define INCLUDE_LEL_CONTEXT_HPP_

#include <utility>

namespace LeL {

struct Identity {
  template <class Value>
  constexpr decltype(auto) operator()(Value &&value) const {
    return std::forward<Value>(value);
  }
};

struct Assign {
  template <class Left, class Right>
  constexpr decltype(auto) operator()(Left &&left, Right &&right) const {
    return std::forward<Left>(left) = std::forward<Right>(right);
  }
};

struct Subscript {
  template <class Left, class Right>
  constexpr decltype(auto) operator()(Left &&left, Right &&right) const {
    return std::forward<Left>(left)[std::forward<Right>(right)];
  }
};

struct Single {};
struct Left {};
struct Right {};
struct Fold {};

template <class ModeT  = Single,
          class ViewLT = Identity,
          class ViewRT = Identity,
          class FuncT  = Identity>
struct Context {
  using Mode  = ModeT;
  using ViewL = ViewLT;
  using ViewR = ViewRT;
  using Func  = FuncT;
};

}  // namespace LeL

#endif  // INCLUDE_LEL_CONTEXT_HPP_
