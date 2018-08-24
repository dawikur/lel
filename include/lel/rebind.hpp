// Copyright 2018, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_REBIND_HPP_
#define INCLUDE_LEL_REBIND_HPP_

#include "lel/context.hpp"
#include "lel/operator.hpp"
#include "lel/operator/binary.hpp"
#include "lel/operator/increment_decrement.hpp"
#include "lel/operator/unary.hpp"

namespace LeL {

template <class From, class To>
struct Rebind {
  using value = std::false_type;

  template <class This, class... View>
  struct context {
    template <class... NewView>
    using with = Context<To, This, NewView...>;
  };
};

template <>
struct Rebind<Operator::PointerToMember, Operator::Call> {
  using value = std::true_type;

  template <class This, class... View>
  struct context {
    template <class... NewView>
    using with = Context<Operator::PointerToMemberCall, View..., NewView...>;
  };
};

}  // namespace LeL

#endif  // INCLUDE_LEL_REBIND_HPP_
