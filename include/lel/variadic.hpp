// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_VARIADIC_HPP_
#define INCLUDE_LEL_VARIADIC_HPP_

#include <utility>

#include "lel/box.hpp"

namespace LeL {

struct Variadic {
  template <int Num>
  struct Get {
    template <class... Values>
    static constexpr decltype(auto) From(Values &&... values) {
      static_assert(Num < sizeof...(values), "Index out of range.");

      return get_impl(Box<int, Num>(), std::forward<Values>(values)...);
    }
  };

 private:
  template <int Num, class Head, class... Tail>
  static constexpr decltype(auto) get_impl(Box<int, Num>,
                                           Head &&,
                                           Tail &&... tail) {
    return get_impl(Box<int, Num - 1>(), std::forward<Tail>(tail)...);
  }

  template <class Head, class... Tail>
  static constexpr decltype(auto) get_impl(Box<int, 0>,
                                           Head &&head,
                                           Tail &&...) {
    return std::forward<Head>(head);
  }
};

}  // namespace LeL

#endif  // INCLUDE_LEL_VARIADIC_HPP_
