// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_SEG_HPP_
#define INCLUDE_SEG_HPP_

#include "seg/operation.hpp"

namespace Seg {

template <char ID>
using Placeholder = Impl<Context<Identity, Identity, Identity, Single>, ID>;

}  // namespace Seg

#endif  // INCLUDE_SEG_HPP_
