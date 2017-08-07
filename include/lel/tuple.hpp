// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_TUPLE_HPP_
#define INCLUDE_LEL_TUPLE_HPP_

#include <tuple>
#include <type_traits>

#include "lel/variadic.hpp"

namespace LeL {

template <class ... Types>
class Tuple {
 public:
  constexpr Tuple(Types &&... types) : impl(std::move(types)...) {}

  template <std::size_t Idx>
  constexpr decltype(auto) get() const {
    return std::get<Idx>(impl);
  }

 private:
  using Raw = std::tuple<Types...>;
  using Impl = typename Variadic::From<Raw>::template RemoveIf<std::is_empty>;

  std::tuple<Types...> const impl;
};

}  // namespace LeL

#endif  // INCLUDE_LEL_TUPLE_HPP_
