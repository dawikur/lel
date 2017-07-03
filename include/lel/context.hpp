// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_CONTEXT_HPP_
#define INCLUDE_LEL_CONTEXT_HPP_

#include <utility>

namespace Lel {

struct Identity {
  template <class Type>
  constexpr auto operator()(Type &&value) const {
    return std::forward<Type>(value);
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

}  // namespace Lel

#endif  // INCLUDE_LEL_CONTEXT_HPP_
