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
  struct IndexOfImpl;

  template <Type... NewTokens>
  struct IndexesOfImpl;

  template <class Merged, class Left, class Right>
  struct MergeImpl;

  template <class Merged, class Left, class Right, bool Condition>
  struct MergeCondition;

  template <class Merged, Type Current, class Left, class Right>
  struct MergeUnique;

 public:
  template <class>
  struct Merge;

  template <Type... NewTokens>
  struct Merge<Self<NewTokens...>> {
    using Result =
      typename MergeImpl<Self<>, Self<Tokens...>, Self<NewTokens...>>::Result;
  };

  template <Type Token>
  static constexpr int IndexOf() {
    return IndexOfImpl<0, Token, Tokens...>::Result::value;
  }

  template <Type... NewTokens>
  using IndexesOf = typename IndexesOfImpl<NewTokens...>::Result;

 private:
  template <int Index, Type Token, Type Head, Type... Tail>
  struct IndexOfImpl<Index, Token, Head, Tail...>
    : public IndexOfImpl<Index + 1, Token, Tail...> {};

  template <int Index, Type Token, Type... Tail>
  struct IndexOfImpl<Index, Token, Token, Tail...> {
    using Result = std::integral_constant<int, Index>;
  };

  template <Type... NewTokens>
  struct IndexesOfImpl {
    using Result = Box<int, IndexOf<NewTokens>()...>;
  };

  // Finish: only left
  template <Type... Merged, Type HeadL, Type... TailL>
  struct MergeImpl<Self<Merged...>, Self<HeadL, TailL...>, Self<>> {
    using Result = Self<Merged..., HeadL, TailL...>;
  };

  // Finish: only right
  template <Type... Merged, Type HeadR, Type... TailR>
  struct MergeImpl<Self<Merged...>, Self<>, Self<HeadR, TailR...>> {
    using Result = Self<Merged..., HeadR, TailR...>;
  };

  // Finish: nothing left to do
  template <Type... Merged>
  struct MergeImpl<Self<Merged...>, Self<>, Self<>> {
    using Result = Self<Merged...>;
  };

  // Compare first elements from Left and Right
  template <Type... Merged,
            Type HeadL,
            Type... TailL,
            Type HeadR,
            Type... TailR>
  struct MergeImpl<Self<Merged...>,
                   Self<HeadL, TailL...>,
                   Self<HeadR, TailR...>>
    : public MergeCondition<Self<Merged...>,
                            Self<HeadL, TailL...>,
                            Self<HeadR, TailR...>,
                            (HeadL < HeadR)> {};

  // Left is lower
  template <Type... Merged,
            Type HeadL,
            Type... TailL,
            Type HeadR,
            Type... TailR>
  struct MergeCondition<Self<Merged...>,
                        Self<HeadL, TailL...>,
                        Self<HeadR, TailR...>,
                        false> : public MergeUnique<Self<Merged...>,
                                                    HeadR,
                                                    Self<HeadL, TailL...>,
                                                    Self<TailR...>> {};

  // Right is lower
  template <Type... Merged,
            Type HeadL,
            Type... TailL,
            Type HeadR,
            Type... TailR>
  struct MergeCondition<Self<Merged...>,
                        Self<HeadL, TailL...>,
                        Self<HeadR, TailR...>,
                        true> : public MergeUnique<Self<Merged...>,
                                                   HeadL,
                                                   Self<TailL...>,
                                                   Self<HeadR, TailR...>> {};

  // Current element is still in Left and Right queue
  template <Type... Merged, Type Current, Type... Left, Type... Right>
  struct MergeUnique<Self<Merged...>,
                     Current,
                     Self<Current, Left...>,
                     Self<Current, Right...>>
    : public MergeUnique<Self<Merged...>, Current, Self<Left...>, Self<Right...>> {
  };

  // Current element is still in Left queue
  template <Type... Merged, Type Current, Type... Left, Type... Right>
  struct MergeUnique<Self<Merged...>, Current, Self<Current, Left...>, Self<Right...>>
    : public MergeUnique<Self<Merged...>, Current, Self<Left...>, Self<Right...>> {
  };

  // Current element is still in Right queue
  template <Type... Merged, Type Current, Type... Left, Type... Right>
  struct MergeUnique<Self<Merged...>, Current, Self<Left...>, Self<Current, Right...>>
    : public MergeUnique<Self<Merged...>, Current, Self<Left...>, Self<Right...>> {
  };

  // Current element is already uqnique
  template <Type... Merged, Type Current, Type... Left, Type... Right>
  struct MergeUnique<Self<Merged...>, Current, Self<Left...>, Self<Right...>>
    : public MergeImpl<Self<Merged..., Current>, Self<Left...>, Self<Right...>> {};
};

template <class Left, class Right>
using Merge = typename Left::template Merge<Right>::Result;

}  // namespace LeL

#endif  // INCLUDE_LEL_BOX_HPP_
