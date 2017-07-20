// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_VARIADIC_HPP_
#define INCLUDE_LEL_VARIADIC_HPP_

#include <utility>

#include "lel/box.hpp"

namespace LeL {

struct Variadic {
 private:
  template <int, class...>
  struct get_type;

 public:
  template <int Num>
  struct Get {
    template <class... Values>
    static constexpr decltype(auto) Value(Values &&... values) {
      static_assert(Num < sizeof...(values), "Index out of range.");

      return get_value(Box<int, Num>(), std::forward<Values>(values)...);
    }

    template <class... Types>
    using Type = typename get_type<Num, Types...>::Result;
  };

 private:
  template <int Num, class Head, class... Tail>
  static constexpr decltype(auto) get_value(Box<int, Num>,
                                            Head &&,
                                            Tail &&... tail) {
    return get_value(Box<int, Num - 1>(), std::forward<Tail>(tail)...);
  }

  template <class Head, class... Tail>
  static constexpr decltype(auto) get_value(Box<int, 0>,
                                            Head &&head,
                                            Tail &&...) {
    return std::forward<Head>(head);
  }

  template <int Num, class Head, class... Tail>
  struct get_type<Num, Head, Tail...> : public get_type<Num - 1, Tail...> {};

  template <class Head, class... Tail>
  struct get_type<0, Head, Tail...> {
    using Result = Head;
  };
};

}  // namespace LeL

#endif  // INCLUDE_LEL_VARIADIC_HPP_
