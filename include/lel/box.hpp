// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_BOX_HPP_
#define INCLUDE_LEL_BOX_HPP_

#include <type_traits>

namespace LeL {

template <class Type, Type... Tokens>
struct Box {
 private:
  template <Type... Values>
  struct Self;

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

  template <class, bool>
  struct PopFrontIf;

  template <class Dummy>
  struct PopFrontIf<Dummy, true> {
    template <Type, Type... Types>
    using From = Self<Types...>;
  };

  template <class Dummy>
  struct PopFrontIf<Dummy, false> {
    template <Type... Types>
    using From = Self<Types...>;
  };

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
                       typename PopFrontIf<bool, (HeadL <= HeadR)>::
                         template From<HeadL, TailL...>,
                       typename PopFrontIf<bool, (HeadR <= HeadL)>::
                         template From<HeadR, TailR...>> {};

 public:
  template <class>
  struct Merge;

  template <Type... NewTokens>
  struct Merge<Box<Type, NewTokens...>> {
    using Result =
      typename MergeImpl<Self<>, Self<Tokens...>, Self<NewTokens...>>::Result;
  };

  template <Type       Token>
  static constexpr int IndexOf() noexcept {
    return IndexOfImpl<0, Token, Tokens...>::Result::value;
  }

  template <Type... NewTokens>
  using IndexesOf = Box<int, (IndexOf<NewTokens>())...>;
};

template <class Left, class Right>
using Merge = typename Left::template Merge<Right>::Result;

}  // namespace LeL

#endif  // INCLUDE_LEL_BOX_HPP_
