// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_TEMPLATE_VARIADIC_HPP_
#define INCLUDE_LEL_TEMPLATE_VARIADIC_HPP_

#include <utility>

#include "lel/template/box.hpp"
#include "lel/context.hpp"

namespace LeL {
namespace Template {

struct Variadic {
 template<int Num>
 using Int = Box<int, Num>;

 public:
  template <int Num>
  struct Get {
    template <class... Values>
    static constexpr decltype(auto) Value(Values &&... values) {
      return GetValueImpl(Int<Num>(), std::forward<Values>(values)...);
    }
  };

 private:
  template <int Num, class Head, class... Tail>
  static constexpr decltype(auto) GetValueImpl(Int<Num>,
                                               Head &&,
                                               Tail &&... tail) {
    return GetValueImpl(Int<Num - 1>(), std::forward<Tail>(tail)...);
  }

  template <class Head, class... Tail>
  static constexpr decltype(auto) GetValueImpl(Int<0>,
                                               Head &&head,
                                               Tail &&...) {
    return std::forward<Head>(head);
  }

  template <int Num>
  static constexpr decltype(auto) GetValueImpl(Int<Num>) {
    return None{};
  }
};

}  // namespace Template
}  // namespace LeL

#endif  // INCLUDE_LEL_TEMPLATE_VARIADIC_HPP_
