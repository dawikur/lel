// Copyright 2018, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_REBIND_HPP_
#define INCLUDE_LEL_REBIND_HPP_

#include <type_traits>

#include "lel/operator.hpp"

namespace LeL {

namespace Operator {

struct Call;
struct PointerToMember;

}  // namespacce Operator

template <class, class>
struct Rebind {
  using value = std::false_type;
};

template <>
struct Rebind<Operator::PointerToMember, Operator::Call> {
  using value = std::true_type;
  using type = Operator::PointerToMemberCall;
};

}  // namespace LeL

#endif  // INCLUDE_LEL_REBIND_HPP_
