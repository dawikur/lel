// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_CONTEXT_HPP_
#define INCLUDE_LEL_CONTEXT_HPP_

#include <utility>

namespace LeL {

template <class Value>
struct Wrap {
  Wrap(Value value) : value(std::move(value)) {}

  template <class... Types>
  constexpr decltype(auto) slice(Types &&...) const {
    return value;
  }

 private:
  Value const value;
};

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

struct Unary {};
struct Binary {};

template <class ModeT  = Unary,
          class LeftT = Identity,
          class RightT = Identity,
          class FuncT  = Identity>
struct Context {
  using Mode  = ModeT;
  using Left  = LeftT;
  using Right = RightT;
  using Func  = FuncT;
};

}  // namespace LeL

#endif  // INCLUDE_LEL_CONTEXT_HPP_
