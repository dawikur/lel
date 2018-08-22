// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_TEMPLATE_SEQUENCE_HPP_
#define INCLUDE_LEL_TEMPLATE_SEQUENCE_HPP_

#include <type_traits>
#include <utility>

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
    : IndexOfImpl<Index + 1, Token, Tail...> {};

  template <int Index, Type Token, Type... Tail>
  struct IndexOfImpl<Index, Token, Token, Tail...> {
    using type = std::integral_constant<int, Index>;
  };

  template <Type...>
  struct BackImpl;

  template <Type Head, Type... Tail>
  struct BackImpl<Head, Tail...> : BackImpl<Tail...> {};

  template <Type Last>
  struct BackImpl<Last> {
    using type = std::integral_constant<Type, Last>;
  };

  template <class, bool>
  struct PopFrontIfImpl;

  template <class Dummy>
  struct PopFrontIfImpl<Dummy, true> {
    template <Type, Type... Tail>
    using type = Sequence<Type, Tail...>;
  };

  template <class Dummy>
  struct PopFrontIfImpl<Dummy, false> {
    template <Type... Types>
    using type = Sequence<Type, Types...>;
  };

 public:
  template <Type Token>
  static constexpr int IndexOf() noexcept {
    return IndexOfImpl<0, Token, Tokens...>::type::value;
  }

  static constexpr Type Back() noexcept {
    return BackImpl<Tokens...>::type::value;
  }

  template <bool Condition>
  using PopFrontIf
    = typename PopFrontIfImpl<bool, Condition>::template type<Tokens...>;

  template <template<class T, T...> class Result>
  using To = Result<Type, Tokens...>;
};

template <std::size_t Num, std::size_t Size>
struct MakeSequenceImpl {
 private:
  template <std::size_t ID, std::size_t N, std::size_t... IDs>
  struct MakeSeqExpand : MakeSeqExpand<ID, N-1, IDs..., ID> {};

  template <std::size_t ID, std::size_t... IDs>
  struct MakeSeqExpand<ID, 0, IDs...> {
    using type = std::index_sequence<IDs...>;
  };

  template <std::size_t ID, std::size_t N, std::size_t S, std::size_t... IDs>
  struct MakeSeq : MakeSeq<ID + 1, N, S, IDs..., ID> {};

  template <std::size_t N, std::size_t S, std::size_t... IDs>
  struct MakeSeq<N, N, S, IDs...> : MakeSeqExpand<N - 1, S, IDs...> {};

 public:
  using type =
    typename MakeSeq<0, Num, (Num < Size ? Size - Num : 0)>::type;
};

template <std::size_t Num, std::size_t Size = Num>
using MakeSequence = typename MakeSequenceImpl<Num, Size>::type;

}  // namespace Template
}  // namespace LeL

#endif  // INCLUDE_LEL_TEMPLATE_SEQUENCE_HPP_
