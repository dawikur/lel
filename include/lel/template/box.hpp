// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_TEMPLATE_BOX_HPP_
#define INCLUDE_LEL_TEMPLATE_BOX_HPP_

#include <functional>

#include "lel/template/sequence.hpp"

namespace LeL {
namespace Template {

template <class Compare, class Type, Type... Tokens>
struct Box {
 private:
  template <Type... Values>
  using Seq = Sequence<Type, Values...>;

  template <Type... Values>
  using Self = Box<Compare, Type, Values...>;

  template <class Merged, class Left, class Right>
  struct MergeImpl;

  // Finish: only left
  template <Type... Merged, Type HeadL, Type... TailL>
  struct MergeImpl<Seq<Merged...>, Seq<HeadL, TailL...>, Seq<>> {
    using Result = Self<Merged..., HeadL, TailL...>;
  };

  // Finish: only right
  template <Type... Merged, Type HeadR, Type... TailR>
  struct MergeImpl<Seq<Merged...>, Seq<>, Seq<HeadR, TailR...>> {
    using Result = Self<Merged..., HeadR, TailR...>;
  };

  // Finish: nothing left to do
  template <Type... Merged>
  struct MergeImpl<Seq<Merged...>, Seq<>, Seq<>> {
    using Result = Self<Merged...>;
  };

  template <Type Left, Type Right>
  static constexpr Type const Lower = Compare()(Left, Right) ? Left : Right;

  // Compare first elements from Left and Right
  template <Type... Merged,
            Type HeadL,
            Type... TailL,
            Type HeadR,
            Type... TailR>
  struct MergeImpl<Seq<Merged...>, Seq<HeadL, TailL...>, Seq<HeadR, TailR...>>
    : public MergeImpl<Seq<Merged..., Lower<HeadL, HeadR>>,
                       typename Seq<HeadL, TailL...>::template PopFrontIf<
                         !Compare()(HeadR, HeadL)>,
                       typename Seq<HeadR, TailR...>::template PopFrontIf<
                         !Compare()(HeadL, HeadR)>> {};

  template <std::size_t Size, Type... NewTokens>
  struct ExpandToImpl
    : ExpandToImpl<Size - 1, NewTokens..., Seq<NewTokens...>::Back()> {};

  template <Type... NewTokens>
  struct ExpandToImpl<0, NewTokens...> {
    using Result = Self<NewTokens...>;
  };

 public:
  template <class... Tail>
  struct Merge : Merge<Seq<>, Tail...> {};

  template <Type... NewTokens, Type... Head, class... Tail>
  struct Merge<Seq<NewTokens...>, Self<Head...>, Tail...>
    : Merge<Seq<NewTokens..., Head...>, Tail...> {};

  template <Type... NewTokens>
  struct Merge<Seq<NewTokens...>> {
    using Result =
      typename MergeImpl<Seq<>, Seq<Tokens...>, Seq<NewTokens...>>::Result;
  };

  template <Type... NewTokens>
  using IndexesOf
    = Box<Compare, int, (Seq<Tokens...>::template IndexOf<NewTokens>())...>;

  template <std::size_t Size>
  using ExpandTo =
    typename ExpandToImpl<Size <= sizeof...(Tokens) ? 0
                                                    : Size - sizeof...(Tokens),
                          Tokens...>::Result;
};

template <class Head, class... Tail>
using Merge = typename Head::template Merge<Tail...>::Result;

}  // namespace Template
}  // namespace LeL

#endif  // INCLUDE_LEL_TEMPLATE_BOX_HPP_
