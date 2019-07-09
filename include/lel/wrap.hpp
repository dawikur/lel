// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_WRAP_HPP_
#define INCLUDE_LEL_WRAP_HPP_

#include <utility>

namespace LeL {

template <class Value>
class Wrap {
 public:
  template <class Type>
  constexpr Wrap(Type &&arg) : value(std::forward<Type>(arg)) {}

  template <class... Types>
  constexpr decltype(auto) operator()(Types &&...) const {
    return value;
  }

 private:
  template <class ID, class... Types>
  constexpr decltype(auto) slice(ID &&, Types &&...) const {
    return value;
  }

  Value const value;

  template <class ContextF, class IDsF>
  friend class Lambda;
};

template <class Value>
class Wrap<Value&> {
 public:
  constexpr Wrap(Value &arg) : value(arg) {}

  template <class... Types>
  constexpr decltype(auto) operator()(Types &&...) const {
    return value;
  }

 private:
  template <class ID, class... Types>
  constexpr decltype(auto) slice(ID &&, Types &&...) const {
    return value;
  }

  Value &value;

  template <class ContextF, class IDsF>
  friend class Lambda;
};

}  // namespace LeL

#endif  // INCLUDE_LEL_WRAP_HPP_
