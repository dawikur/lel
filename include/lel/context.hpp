// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_CONTEXT_HPP_
#define INCLUDE_LEL_CONTEXT_HPP_

#include <utility>

namespace LeL {

struct None {};

struct Identity {
  template <class Value>
  constexpr decltype(auto) operator()(Value &&value) const noexcept {
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

template <class Func, class ... Views>
struct Context {};

}  // namespace LeL

#endif  // INCLUDE_LEL_CONTEXT_HPP_
