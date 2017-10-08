// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_TEMPLATE_SEQUENCE_HPP_
#define INCLUDE_LEL_TEMPLATE_SEQUENCE_HPP_

#include <type_traits>

namespace LeL {
namespace Template {

template <class Type, Type... Tokens>
struct Sequence {
 private:
  template <int Index, Type Token, Type... Tail>
  struct IndexOfImpl {
    static_assert(sizeof...(Tail) != 0, "Index not found");
  };

  template <int Index, Type Token, Type Head, Type... Tail>
  struct IndexOfImpl<Index, Token, Head, Tail...>
    : public IndexOfImpl<Index + 1, Token, Tail...> {};

  template <int Index, Type Token, Type... Tail>
  struct IndexOfImpl<Index, Token, Token, Tail...> {
    using Result = std::integral_constant<int, Index>;
  };

 public:
  template <Type       Token>
  static constexpr int IndexOf() noexcept {
    return IndexOfImpl<0, Token, Tokens...>::Result::value;
  }
};

}  // namespace Template
}  // namespace LeL

#endif  // INCLUDE_LEL_TEMPLATE_SEQUENCE_HPP_
