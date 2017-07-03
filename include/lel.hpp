// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_HPP_
#define INCLUDE_LEL_HPP_

#include "lel/operation.hpp"

namespace Lel {

template <char ID>
using Placeholder
  = Impl<Context<Identity, Identity, Identity, Single>, Box<char, ID>>;

}  // namespace Lel

#endif  // INCLUDE_LEL_HPP_
