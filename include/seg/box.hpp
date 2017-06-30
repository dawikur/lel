// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_SEG_BOX_HPP_
#define INCLUDE_SEG_BOX_HPP_

namespace Seg {

template <class Type, Type... Tokens>
struct Box {
  template <class>
  struct Merge;

  template <Type... NewTokens>
  struct Merge<Box<Type, NewTokens...>> {
    using Result = Box<Type, Tokens..., NewTokens...>;
  };
};

template <class Left, class Right>
using Merge = typename Left::template Merge<Right>::Result;

}  // namespace Seg

#endif  // INCLUDE_SEG_BOX_HPP_
