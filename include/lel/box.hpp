// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_BOX_HPP_
#define INCLUDE_LEL_BOX_HPP_

#include <type_traits>

namespace LeL {

template <class Type, Type... Tokens>
struct Box {
 private:
  template <Type... Values>
  using Self = Box<Type, Values...>;

  template <int Index, Type Token, Type... Tail>
  struct IndexOfImpl {
    static_assert(sizeof...(Tail) != 0, "Index not found");
  };

  template <class Merged, class Left, class Right>
  struct MergeImpl;

 public:
  template <class>
  struct Merge;

  template <Type... NewTokens>
  struct Merge<Self<NewTokens...>> {
    using Result =
      typename MergeImpl<Self<>, Self<Tokens...>, Self<NewTokens...>>::Result;
  };

  template <Type       Token>
  static constexpr int IndexOf() noexcept {
    return IndexOfImpl<0, Token, Tokens...>::Result::value;
  }

  template <Type... NewTokens>
  using IndexesOf = Box<int, (IndexOf<NewTokens>())...>;

 private:
  template <int Index, Type Token, Type Head, Type... Tail>
  struct IndexOfImpl<Index, Token, Head, Tail...>
    : public IndexOfImpl<Index + 1, Token, Tail...> {};

  template <int Index, Type Token, Type... Tail>
  struct IndexOfImpl<Index, Token, Token, Tail...> {
    using Result = std::integral_constant<int, Index>;
  };

  // Finish: only left
  template <Type... Merged, Type... Left>
  struct MergeImpl<Self<Merged...>, Self<Left...>, Self<>> {
    using Result = Self<Merged..., Left...>;
  };

  // Finish: only right
  template <Type... Merged, Type... Right>
  struct MergeImpl<Self<Merged...>, Self<>, Self<Right...>> {
    using Result = Self<Merged..., Right...>;
  };

  // Finish: nothing left to do
  template <Type... Merged>
  struct MergeImpl<Self<Merged...>, Self<>, Self<>> {
    using Result = Self<Merged...>;
  };

  // Heads are the same in Left and Right
  template <Type... Merged,
            Type Head,
            Type... TailL,
            Type... TailR>
  struct MergeImpl<Self<Merged...>,
                   Self<Head, TailL...>,
                   Self<Head, TailR...>>
    : public MergeImpl<Self<Merged..., Head>,
                       Self<TailL...>,
                       Self<TailR...>> {};

  template <Type Left, Type Right>
  static constexpr Type const Lower = Left < Right ? Left : Right;

  template <class Left, class Right, bool Condition>
  struct Choose;

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
                       typename Choose<Self<HeadL, TailL...>,
                                       Self<HeadR, TailR...>,
                                       (HeadL < HeadR)>::Left,
                       typename Choose<Self<HeadL, TailL...>,
                                       Self<HeadR, TailR...>,
                                       (HeadL < HeadR)>::Right> {};

  // Left is lower
  template <Type... TailL, Type HeadR, Type... TailR>
  struct Choose<Self<TailL...>, Self<HeadR, TailR...>, false> {
    using Left  = Self<TailL...>;
    using Right = Self<TailR...>;
  };

  // Right is lower
  template <Type HeadL, Type... TailL, Type... TailR>
  struct Choose<Self<HeadL, TailL...>, Self<TailR...>, true> {
    using Left  = Self<TailL...>;
    using Right = Self<TailR...>;
  };

  // TODO: 2017-07-10 check if sequences are sored & unique
};

template <class Left, class Right>
using Merge = typename Left::template Merge<Right>::Result;

}  // namespace LeL

#endif  // INCLUDE_LEL_BOX_HPP_
