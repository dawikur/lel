// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_SEG_UTILITY_HPP_
#define INCLUDE_SEG_UTILITY_HPP_

namespace Seg {

struct Identity {
  template <class Type>
  constexpr auto operator()(Type const &value) const {
    return value;
  }
};

struct Single {};
struct Left {};
struct Right {};
struct Both {};
struct Fold {};

template <class ViewLT, class ViewRT, class FuncT, class ModeT>
struct Context {
  using ViewL = ViewLT;
  using ViewR = ViewRT;
  using Func  = FuncT;
  using Mode  = ModeT;
};

template <class Type, Type... Tokens>
struct Box {
  template <class>
  struct Merge;

  template <Type... NewTokens>
  struct Merge<Box<Type, NewTokens...>> {
    using Result = Box<Type, Tokens...>;
  };
};

template <class Left, class Right>
using Merge = typename Left::template Merge<Right>::Result;

}  // namespace Seg

#endif  // INCLUDE_SEG_UTILITY_HPP_
