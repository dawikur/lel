// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_CONTEXT_HPP_
#define INCLUDE_LEL_CONTEXT_HPP_

#include <utility>

namespace LeL {

struct Identity {
  template <class Type>
  constexpr decltype(auto) operator()(Type &&value) const {
    return std::forward<Type>(value);
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

template <class ViewLT = Identity,
          class ViewRT = Identity,
          class FuncT  = Identity,
          class ModeT  = Single>
struct Context {
  using ViewL = ViewLT;
  using ViewR = ViewRT;
  using Func  = FuncT;
  using Mode  = ModeT;
};

}  // namespace LeL

#endif  // INCLUDE_LEL_CONTEXT_HPP_
