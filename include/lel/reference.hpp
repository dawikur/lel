// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_REFERENCE_HPP_
#define INCLUDE_LEL_REFERENCE_HPP_

#include "lel/lambda.hpp"

namespace LeL {

template <class ID>
struct Reference {
  template <class Value>
  constexpr decltype(auto) operator()(Value &&value) const {
    return Lambda<Context<Identity, Wrap<Value &>>, Box<ID>>(
      Wrap<Value &>(value));
  }
};

}  // namespace LeL

#endif  // INCLUDE_LEL_REFERENCE_HPP_
