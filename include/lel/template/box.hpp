// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_TEMPLATE_BOX_HPP_
#define INCLUDE_LEL_TEMPLATE_BOX_HPP_

#include <functional>

#include "lel/template/sequence.hpp"

namespace LeL {
namespace Template {

template <class Type, Type... Tokens>
struct Box {
 private:
  template <Type... Values>
  using Self = Sequence<Type, Values...>;

  template <class Merged, class Left, class Right>
  struct MergeImpl;

  // Finish: only left
  template <Type... Merged, Type HeadL, Type... TailL>
  struct MergeImpl<Self<Merged...>, Self<HeadL, TailL...>, Self<>> {
    using Result = Box<Type, Merged..., HeadL, TailL...>;
  };

  // Finish: only right
  template <Type... Merged, Type HeadR, Type... TailR>
  struct MergeImpl<Self<Merged...>, Self<>, Self<HeadR, TailR...>> {
    using Result = Box<Type, Merged..., HeadR, TailR...>;
  };

  // Finish: nothing left to do
  template <Type... Merged>
  struct MergeImpl<Self<Merged...>, Self<>, Self<>> {
    using Result = Box<Type, Merged...>;
  };

  template <Type Left, Type Right>
  static constexpr Type const Lower = Left < Right ? Left : Right;

  // Compare first elements from Left and Right
  template <Type... Merged,
            Type HeadL,
            Type... TailL,
            Type HeadR,
            Type... TailR>
  struct MergeImpl<Self<Merged...>,
                   Self<HeadL, TailL...>,
                   Self<HeadR, TailR...>>
    : public MergeImpl<Self<Merged..., Lower<HeadL, HeadR>>,
                       typename Self<HeadL, TailL...>::
                         template PopFrontIf<HeadL <= HeadR>,
                       typename Self<HeadR, TailR...>::
                         template PopFrontIf<HeadR <= HeadL>> {};

  template <std::size_t Size, Type... NewTokens>
  struct ExpandToImpl
    : ExpandToImpl<Size - 1, NewTokens..., Self<NewTokens...>::Back()> {};

  template <Type... NewTokens>
  struct ExpandToImpl<0, NewTokens...> {
    using Result = Box<Type, NewTokens...>;
  };

 public:
  template <class... Tail>
  struct Merge : Merge<Self<>, Tail...> {};

  template <Type... NewTokens, Type... Head, class... Tail>
  struct Merge<Self<NewTokens...>, Box<Type, Head...>, Tail...>
    : Merge<Self<NewTokens..., Head...>, Tail...> {};

  template <Type... NewTokens>
  struct Merge<Self<NewTokens...>> {
    using Result =
      typename MergeImpl<Self<>, Self<Tokens...>, Self<NewTokens...>>::Result;
  };

  template <Type... NewTokens>
  using IndexesOf
    = Box<int, (Sequence<Type, Tokens...>::template IndexOf<NewTokens>())...>;

  template <std::size_t Size>
  using ExpandTo =
    typename ExpandToImpl<Size <= sizeof...(Tokens) ? 0
                                                    : Size - sizeof...(Tokens),
                          Tokens...>::Result;
};

template <class Head, class ...Tail>
using Merge = typename Head::template Merge<Tail...>::Result;

}  // namespace Template
}  // namespace LeL

#endif  // INCLUDE_LEL_TEMPLATE_BOX_HPP_
