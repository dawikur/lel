// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_LAMBDA_HPP_
#define INCLUDE_LEL_LAMBDA_HPP_

#include <utility>

#include "lel/context.hpp"
#include "lel/variadic.hpp"

namespace LeL {

template <class Context, class IDs>
class Lambda;

template <class Value>
class Lambda<Value, Box<char>> {
  using ID = Box<char>;

 public:
  constexpr Lambda(Value value) : value(std::move(value)) {}

  template <class... Types>
  constexpr decltype(auto) operator()(Types &&...) const {
    return value;
  }

  template <class... Types>
  constexpr decltype(auto) slice(Types &&...) const {
    return value;
  }

 private:
  Value const value;
};

template <class Context, char... IDs>
class Lambda<Context, Box<char, IDs...>> {
  using ID = Box<char, IDs...>;

 public:
  constexpr Lambda() : left(), right() {}

  constexpr Lambda(typename Context::Left left, typename Context::Right right)
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
                               Lambda<Context, ID>,
                               Lambda<Value, Box<char>>,
                               Assign>,
                  ID>{*this, std::move(value)};
  }

  template <class RestV, class IDV>
  constexpr decltype(auto) operator=(Lambda<RestV, IDV> viewV) const {
    return Lambda<LeL::Context<Binary,
                               Lambda<Context, ID>,
                               Lambda<RestV, IDV>,
                               Assign>,
                  Merge<ID, IDV>>{*this, std::move(viewV)};
  }

  template <class Value>
  constexpr decltype(auto) operator[](Value value) const {
    return Lambda<LeL::Context<Binary,
                               Lambda<Context, ID>,
                               Lambda<Value, Box<char>>,
                               Subscript>,
                  ID>{*this, std::move(value)};
  }

  template <class RestV, class IDV>
  constexpr decltype(auto) operator[](Lambda<RestV, IDV> viewV) const {
    return Lambda<LeL::Context<Binary,
                               Lambda<Context, ID>,
                               Lambda<RestV, IDV>,
                               Subscript>,
                  Merge<ID, IDV>>{*this, std::move(viewV)};
  }

 private:
  template <class... Values>
  constexpr decltype(auto) call(Unary, Values &&... values) const {
    return typename Context::Func()(left(std::forward<Values>(values)...));
  }

  template <class... Values>
  constexpr decltype(auto) call(Binary, Values &&... values) const {
    return typename Context::Func()(left.slice(ID(), values...),
                                    right.slice(ID(), values...));
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

  typename Context::Left const  left;
  typename Context::Right const right;

  template <class ContextF, class IDsF>
  friend class Lambda;
};

}  // namespace LeL

#endif  // INCLUDE_LEL_LAMBDA_HPP_
