// Copyright 2018, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_REBIND_HPP_
#define INCLUDE_LEL_REBIND_HPP_

#include <type_traits>

#include "lel/functor.hpp"

namespace LeL {

struct Call;

namespace Operator {

struct PointerToMember;

}  // namespacce Operator

template <class, class>
struct Rebind {
  using value = std::false_type;
};

template <>
struct Rebind<Operator::PointerToMember, Call> {
  using value = std::true_type;
  using type = PointerToMemberCall;
};

}  // namespace LeL

#endif  // INCLUDE_LEL_REBIND_HPP_
