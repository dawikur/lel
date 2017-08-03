// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_VARIADIC_HPP_
#define INCLUDE_LEL_VARIADIC_HPP_

#include <utility>

#include "lel/box.hpp"
#include "lel/context.hpp"

namespace LeL {

struct Variadic {
 private:
  template <int, class...>
  struct GetTypeImpl;

  template <class, template <class> class, class...>
  struct FilterWithImpl;

 public:
  template <int Num>
  struct Get {
    template <class... Values>
    static constexpr decltype(auto) Value(Values &&... values) {
      return GetValueImpl(Box<int, Num>(), std::forward<Values>(values)...);
    }

    template <class... Types>
    using Type = typename GetTypeImpl<Num, Types...>::Result;
  };

  template <class Type>
  struct Filter;

  template <template <class...> class Wrap, class... Types>
  struct Filter<Wrap<Types...>> {
    template <template <class> class Predicate>
    using With = typename FilterWithImpl<Wrap<>, Predicate, Types...>::Result;
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

  template <int Num, class Head, class... Tail>
  struct GetTypeImpl<Num, Head, Tail...>
    : public GetTypeImpl<Num - 1, Tail...> {};

  template <class Head, class... Tail>
  struct GetTypeImpl<0, Head, Tail...> {
    using Result = Head;
  };

  template <class, bool>
  struct If;

  template <class Dummy>
  struct If<Dummy, false> {
    template <template <class...> class Wrap, class Head, class... Tail>
    using Append = Wrap<Tail..., Head>;
  };

  template <class Dummy>
  struct If<Dummy, true> {
    template <template <class...> class Wrap, class, class... Tail>
    using Append = Wrap<Tail...>;
  };

  template <template <class...> class Wrap,
            template <class> class Predicate,
            class... Filtered,
            class Head,
            class... Tail>
  struct FilterWithImpl<Wrap<Filtered...>, Predicate, Head, Tail...>
    : FilterWithImpl<typename If<bool, Predicate<Head>::value>::
                       template Append<Wrap, Head, Filtered...>,
                     Predicate,
                     Tail...> {};

  template <template <class...> class Wrap,
            template <class> class Predicate,
            class... Filtered>
  struct FilterWithImpl<Wrap<Filtered...>, Predicate> {
    using Result = Wrap<Filtered...>;
  };
};

}  // namespace LeL

#endif  // INCLUDE_LEL_VARIADIC_HPP_
