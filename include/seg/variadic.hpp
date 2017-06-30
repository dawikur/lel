// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_SEG_VARIADIC_HPP_
#define INCLUDE_SEG_VARIADIC_HPP_

namespace Seg {

struct Variadic {

  template<int Num, class...Values>
  constexpr auto get(Values&& ...values) const {
  }

};

}  // namespace Seg

#endif  // INCLUDE_SEG_VARIADIC_HPP_
