// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_REFERENCE_HPP_
#define INCLUDE_LEL_REFERENCE_HPP_

#include "lel/lambda.hpp"

namespace LeL {

struct Reference {
  template <class Value>
  constexpr decltype(auto) operator()(Value &value) {
    return Lambda<Context<Identity, Wrap<Value &>>, Box<char>>(
      Wrap<Value &>(value));
  }
};

}  // namespace LeL

#endif  // INCLUDE_LEL_REFERENCE_HPP_
