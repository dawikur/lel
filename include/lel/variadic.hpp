// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_VARIADIC_HPP_
#define INCLUDE_LEL_VARIADIC_HPP_

#include <utility>

#include "lel/box.hpp"
#include "lel/context.hpp"

namespace LeL {

struct Variadic {
 public:
  template <int Num>
  struct Get {
    template <class... Values>
    static constexpr decltype(auto) Value(Values &&... values) {
      return GetValueImpl(Box<int, Num>(), std::forward<Values>(values)...);
    }
  };

 private:
  template <int Num, class Head, class... Tail>
  static constexpr decltype(auto) GetValueImpl(Box<int, Num>,
                                               Head &&,
                                               Tail &&... tail) {
    return GetValueImpl(Box<int, Num - 1>(), std::forward<Tail>(tail)...);
  }

  template <class Head, class... Tail>
  static constexpr decltype(auto) GetValueImpl(Box<int, 0>,
                                               Head &&head,
                                               Tail &&...) {
    return std::forward<Head>(head);
  }

  template <int Num>
  static constexpr decltype(auto) GetValueImpl(Box<int, Num>) {
    return None{};
  }
};

}  // namespace LeL

#endif  // INCLUDE_LEL_VARIADIC_HPP_
