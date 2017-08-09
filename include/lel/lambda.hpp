// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_LAMBDA_HPP_
#define INCLUDE_LEL_LAMBDA_HPP_

#include <utility>

#include "lel/context.hpp"
#include "lel/tuple.hpp"
#include "lel/variadic.hpp"
#include "lel/wrap.hpp"

namespace LeL {

template <class Context, class IDs>
class Lambda;

template <class Func, class... Views, char... IDs>
class Lambda<Context<Func, Views...>, Box<char, IDs...>> : Tuple<Views...> {
  using ID = Box<char, IDs...>;
  using Class = Lambda<Context<Func, Views...>, ID>;
  using Impl = Tuple<Views...>;

 public:
  constexpr Lambda(Views... views) : Impl(std::move(views)...) {}

  template <class... Values>
  constexpr decltype(auto) operator()(Values &&... values) const {
    static_assert(sizeof...(IDs) >= sizeof...(values),
                  "Incorrect number of arguments");

    return call(std::make_index_sequence<sizeof...(Views)>(),
                std::forward<Values>(values)...);
  }

  template <class Value>
  constexpr decltype(auto) operator=(Value &&value) const {
    return Lambda<Context<Assign, Class, Wrap<Value const>>, ID>{
      *this, std::forward<Value>(value)};
  }

  template <class RestV, class IDV>
  constexpr decltype(auto) operator=(Lambda<RestV, IDV> view) const {
    return Lambda<Context<Assign, Class, Lambda<RestV, IDV>>, Merge<ID, IDV>>{
      *this, std::move(view)};
  }

  template <class Value>
  constexpr decltype(auto) operator[](Value &&value) const {
    return Lambda<Context<Subscript, Class, Wrap<Value const>>, ID>{
      *this, std::forward<Value>(value)};
  }

  template <class RestV, class IDV>
  constexpr decltype(auto) operator[](Lambda<RestV, IDV> view) const {
    return Lambda<Context<Subscript, Class, Lambda<RestV, IDV>>,
                  Merge<ID, IDV>>{*this, std::move(view)};
  }

 private:
  template <char... Slice, class... Values>
  constexpr decltype(auto) slice(Box<char, Slice...>,
                                 Values &&... values) const {
    using Indexes = typename Box<char, Slice...>::template IndexesOf<IDs...>;

    return slice(Indexes(), std::forward<Values>(values)...);
  }

  template <int... Indexes, class... Values>
  constexpr decltype(auto) slice(Box<int, Indexes...>,
                                 Values &&... values) const {
    return operator()(
      Variadic::Get<Indexes>::Value(std::forward<Values>(values)...)...);
  }

  template <class... Values>
  constexpr decltype(auto) call(std::index_sequence<>,
                                Values &&... values) const {
    return Func()(std::forward<Values>(std::forward<Values>(values))...);
  }

  template <std::size_t... Idx, class... Values>
  constexpr decltype(auto) call(std::index_sequence<Idx...>,
                                Values &&... values) const {
    return Func()(Impl::template get<Idx>().slice(
      ID(), std::forward<Values>(values)...)...);
  }

  constexpr decltype(auto) operator()(None const) const {
    return *this;
  }

  template <class ContextF, class IDsF>
  friend class Lambda;
};

}  // namespace LeL

#endif  // INCLUDE_LEL_LAMBDA_HPP_
