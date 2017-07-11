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
  using Class = Lambda<Value, ID>;

 public:
  constexpr Lambda(Value value) : value(std::move(value)) {}

  template <class... Types>
  constexpr decltype(auto) operator()(Types &&...) const {
    return value;
  }

  template <class ID, class... Types>
  constexpr decltype(auto) slice(ID &&, Types &&...) const {
    return value;
  }

 private:
  Value const value;
};

template <char IDs>
class Lambda<Identity, Box<char, IDs>> {
  using ID = Box<char, IDs>;
  using Class = Lambda<Identity, ID>;

 public:
  template <class Value>
  constexpr decltype(auto) operator()(Value && value) const {
    return std::forward<Value>(value);
  }

  // () function call

  template <class Value>
  constexpr decltype(auto) operator=(Value value) const {
    return Lambda<Binary<Class, Lambda<Value, Box<char>>, Assign>, ID>{
      *this, std::move(value)};
  }

  template <class RestV, class IDV>
  constexpr decltype(auto) operator=(Lambda<RestV, IDV> viewV) const {
    return Lambda<Binary<Class, Lambda<RestV, IDV>, Assign>, Merge<ID, IDV>>{
      *this, std::move(viewV)};
  }

  template <class Value>
  constexpr decltype(auto) operator[](Value value) const {
    return Lambda<Binary<Class, Lambda<Value, Box<char>>, Subscript>, ID>{
      *this, std::move(value)};
  }

  template <class RestV, class IDV>
  constexpr decltype(auto) operator[](Lambda<RestV, IDV> viewV) const {
    return Lambda<Binary<Class, Lambda<RestV, IDV>, Subscript>, Merge<ID, IDV>>{
      *this, std::move(viewV)};
  }

  template <char... Slice, class... Values>
  constexpr decltype(auto) slice(Box<char, Slice...>,
                                 Values &&... values) const {
    using Indexes = typename Box<char, Slice...>::template IndexesOf<IDs>;

    return slice(Indexes(), std::forward<Values>(values)...);
  }

 private:
  template <int... Indexes, class... Values>
  constexpr decltype(auto) slice(Box<int, Indexes...>,
                                 Values &&... values) const {
    return operator()(Variadic().Get<Indexes>(values...)...);
  }

};

template <class View, class Func, char... IDs>
class Lambda<Unary<View, Func>, Box<char, IDs...>> {
  using ID = Box<char, IDs...>;
  using Class = Lambda<Unary<View, Func>, ID>;

 public:
  constexpr Lambda(View view) : view(std::move(view)) {}

  template <class... Values>
  constexpr decltype(auto) operator()(Values &&... values) const {
    static_assert(sizeof...(IDs) == sizeof...(values),
                  "Incorrect number of arguments");

    return Func()(view(std::forward<Values>(values)...));
  }

  // () function call

  template <class Value>
  constexpr decltype(auto) operator=(Value value) const {
    return Lambda<Binary<Class, Lambda<Value, Box<char>>, Assign>, ID>{
      *this, std::move(value)};
  }

  template <class RestV, class IDV>
  constexpr decltype(auto) operator=(Lambda<RestV, IDV> viewV) const {
    return Lambda<Binary<Class, Lambda<RestV, IDV>, Assign>, Merge<ID, IDV>>{
      *this, std::move(viewV)};
  }

  template <class Value>
  constexpr decltype(auto) operator[](Value value) const {
    return Lambda<Binary<Class, Lambda<Value, Box<char>>, Subscript>, ID>{
      *this, std::move(value)};
  }

  template <class RestV, class IDV>
  constexpr decltype(auto) operator[](Lambda<RestV, IDV> viewV) const {
    return Lambda<Binary<Class, Lambda<RestV, IDV>, Subscript>, Merge<ID, IDV>>{
      *this, std::move(viewV)};
  }

  template <char... Slice, class... Values>
  constexpr decltype(auto) slice(Box<char, Slice...>,
                                 Values &&... values) const {
    using Indexes = typename Box<char, Slice...>::template IndexesOf<IDs...>;

    return slice(Indexes(), std::forward<Values>(values)...);
  }

 private:
  template <int... Indexes, class... Values>
  constexpr decltype(auto) slice(Box<int, Indexes...>,
                                 Values &&... values) const {
    return operator()(Variadic().Get<Indexes>(values...)...);
  }

  View const view;

  template <class ContextF, class IDsF>
  friend class Lambda;
};

template <class Left, class Right, class Func, char... IDs>
class Lambda<Binary<Left, Right, Func>, Box<char, IDs...>> {
  using ID = Box<char, IDs...>;
  using Class = Lambda<Binary<Left, Right, Func>, ID>;

 public:
  constexpr Lambda(Left left, Right right)
    : left(std::move(left)), right(std::move(right)) {}

  template <class... Values>
  constexpr decltype(auto) operator()(Values &&... values) const {
    static_assert(sizeof...(IDs) == sizeof...(values),
                  "Incorrect number of arguments");

    return Func()(left.slice(ID(), values...), right.slice(ID(), values...));
  }

  // () function call

  template <class Value>
  constexpr decltype(auto) operator=(Value value) const {
    return Lambda<Binary<Class, Lambda<Value, Box<char>>, Assign>, ID>{
      *this, std::move(value)};
  }

  template <class RestV, class IDV>
  constexpr decltype(auto) operator=(Lambda<RestV, IDV> viewV) const {
    return Lambda<Binary<Class, Lambda<RestV, IDV>, Assign>, Merge<ID, IDV>>{
      *this, std::move(viewV)};
  }

  template <class Value>
  constexpr decltype(auto) operator[](Value value) const {
    return Lambda<Binary<Class, Lambda<Value, Box<char>>, Subscript>, ID>{
      *this, std::move(value)};
  }

  template <class RestV, class IDV>
  constexpr decltype(auto) operator[](Lambda<RestV, IDV> viewV) const {
    return Lambda<Binary<Class, Lambda<RestV, IDV>, Subscript>, Merge<ID, IDV>>{
      *this, std::move(viewV)};
  }

  template <char... Slice, class... Values>
  constexpr decltype(auto) slice(Box<char, Slice...>,
                                 Values &&... values) const {
    using Indexes = typename Box<char, Slice...>::template IndexesOf<IDs...>;

    return slice(Indexes(), std::forward<Values>(values)...);
  }

 private:
  template <int... Indexes, class... Values>
  constexpr decltype(auto) slice(Box<int, Indexes...>,
                                 Values &&... values) const {
    return operator()(Variadic().Get<Indexes>(values...)...);
  }

  Left const  left;
  Right const right;

  template <class ContextF, class IDsF>
  friend class Lambda;
};

}  // namespace LeL

#endif  // INCLUDE_LEL_LAMBDA_HPP_
