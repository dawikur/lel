// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_LAMBDA_HPP_
#define INCLUDE_LEL_LAMBDA_HPP_

#include <utility>

#include "lel/context.hpp"
#include "lel/variadic.hpp"

namespace LeL {

template <class Context, class IDs>
struct Lambda;

template <class Context, char... IDs>
struct Lambda<Context, Box<char, IDs...>> {
  using MyIDs = Box<char, IDs...>;

 public:
  constexpr Lambda() : left(), right() {}

  constexpr Lambda(typename Context::ViewL left, typename Context::ViewR right)
    : left(std::move(left)), right(std::move(right)) {}

  template <class... Values>
  constexpr decltype(auto) operator()(Values &&... values) const {
    static_assert(sizeof...(IDs) == sizeof...(values),
                  "Incorrect number of arguments");

    return call(typename Context::Mode(), std::forward<Values>(values)...);
  }

  // () function call

  template <class Value>
  constexpr decltype(auto) operator=(Value value) const {
    return Lambda<LeL::Context<Binary,
                               Lambda<Context, MyIDs>,
                               Wrap<Value>,
                               Assign>,
                  MyIDs>{*this, std::move(value)};
  }

  template <class RestV, class IDV>
  constexpr decltype(auto) operator=(Lambda<RestV, IDV> viewV) const {
    return Lambda<LeL::Context<Binary,
                               Lambda<Context, MyIDs>,
                               Lambda<RestV, IDV>,
                               Assign>,
                  Merge<MyIDs, IDV>>{*this, std::move(viewV)};
  }

  template <class Value>
  constexpr decltype(auto) operator[](Value value) const {
    return Lambda<LeL::Context<Binary,
                               Lambda<Context, MyIDs>,
                               Wrap<Value>,
                               Subscript>,
                  MyIDs>{*this, std::move(value)};
  }

  template <class RestV, class IDV>
  constexpr decltype(auto) operator[](Lambda<RestV, IDV> viewV) const {
    return Lambda<LeL::Context<Binary,
                               Lambda<Context, MyIDs>,
                               Lambda<RestV, IDV>,
                               Subscript>,
                  Merge<MyIDs, IDV>>{*this, std::move(viewV)};
  }

 private:
  template <class... Values>
  constexpr decltype(auto) call(Unary, Values &&... values) const {
    return typename Context::Func()(left(std::forward<Values>(values)...));
  }

  template <class... Values>
  constexpr decltype(auto) call(Binary, Values &&... values) const {
    return typename Context::Func()(left.slice(MyIDs(), values...),
                                    right.slice(MyIDs(), values...));
  }

  template <char... Slice, class... Values>
  constexpr decltype(auto) slice(Box<char, Slice...>,
                                 Values &&... values) const {
    using Indexes = typename Box<char, Slice...>::template IndexesOf<IDs...>;

    return slice(Indexes(), std::forward<Values>(values)...);
  }

  template <int... Indexes, class... Values>
  constexpr decltype(auto) slice(Box<int, Indexes...>,
                                 Values &&... values) const {
    return call(typename Context::Mode(),
                Variadic().Get<Indexes>(values...)...);
  }

  typename Context::ViewL const left;
  typename Context::ViewR const right;

  template <class ContextF, class IDsF>
  friend struct Lambda;
};

}  // namespace LeL

#endif  // INCLUDE_LEL_LAMBDA_HPP_
