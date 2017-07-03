// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_VARIADIC_HPP_
#define INCLUDE_LEL_VARIADIC_HPP_

#include <utility>

#include "lel/box.hpp"

namespace Lel {

struct Variadic {

  template<int Num, class...Values>
  constexpr auto Get(Values&& ...values) const {
    static_assert(Num < sizeof...(values), "Index out range.");

    return get_impl(Box<int, Num>(), std::forward<Values>(values)...);
  }

 private:
  template <int  Num, class Head, class... Tail>
  constexpr auto get_impl(Box<int, Num>, Head &&head, Tail &&... tail) const {
    return get_impl(Box<int, Num - 1>(), std::forward<Tail>(tail)...);
  }

  template <class Head, class... Tail>
  constexpr auto get_impl(Box<int, 0>, Head &&head, Tail &&... tail) const {
    return std::forward<Head>(head);
  }
};

}  // namespace Lel

#endif  // INCLUDE_LEL_VARIADIC_HPP_