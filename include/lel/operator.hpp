// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_OPERATOR_HPP_
#define INCLUDE_LEL_OPERATOR_HPP_

#include <utility>

namespace LeL {
namespace Operator {

struct Identity {
  template <class Value>
  constexpr decltype(auto) operator()(Value &&value) const noexcept {
    return std::forward<Value>(value);
  }
};

struct Assign {
  template <class Left, class Right>
  constexpr auto& operator()(Left &&left, Right &&right) const {
    return std::forward<Left>(left) = std::forward<Right>(right);
  }
};

struct Subscript {
  template <class Left, class Right>
  constexpr decltype(auto) operator()(Left &&left, Right &&right) const {
    return std::forward<Left>(left)[std::forward<Right>(right)];
  }
};

struct Call {
  template <class Callable, class... Args>
  constexpr decltype(auto) operator()(Callable &&callable,
                                      Args &&... args) const {
    return std::forward<Callable>(callable)(std::forward<Args>(args)...);
  }
};

struct PointerToMemberCall {
  template <class Pointer, class Member, class... Args>
  constexpr decltype(auto) operator()(Pointer &&pointer,
                                      Member && member,
                                      Args &&... args) const {
    return (std::forward<Pointer>(pointer)->*std::forward<Member>(member))(
      std::forward<Args>(args)...);
    }
};

}  // namespace Opeator
}  // namespace LeL

#endif  // INCLUDE_LEL_OPERATOR_HPP_
