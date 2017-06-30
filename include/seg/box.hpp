// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_SEG_BOX_HPP_
#define INCLUDE_SEG_BOX_HPP_

#include <type_traits>

namespace Seg {

template <class Type, Type... Tokens>
struct Box {
 private:
  template <Type... Values>
  using Self = Box<Type, Values...>;

  template <class Merged, class Left, class Right>
  struct MergeImpl;

  template <class Merged, class Left, class Right, bool Condition>
  struct MergeCondition;

  template <class Merged, Type Last, class Left, class Right>
  struct MergeUnique;

 public:
  template <class>
  struct Merge;

  template <Type... NewTokens>
  struct Merge<Self<NewTokens...>> {
    using Result =
      typename MergeImpl<Self<>, Self<Tokens...>, Self<NewTokens...>>::Result;
  };

 private:
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

  template <Type... Merged, Type HeadL, Type... TailL>
  struct MergeImpl<Self<Merged...>, Self<HeadL, TailL...>, Self<>> {
    using Result = Self<Merged..., HeadL, TailL...>;
  };

  template <Type... Merged, Type HeadR, Type... TailR>
  struct MergeImpl<Self<Merged...>, Self<>, Self<HeadR, TailR...>> {
    using Result = Self<Merged..., HeadR, TailR...>;
  };

  template <Type... Merged>
  struct MergeImpl<Self<Merged...>, Self<>, Self<>> {
    using Result = Self<Merged...>;
  };

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

  template <Type... Merged, Type Last, Type... Left, Type... Right>
  struct MergeUnique<Self<Merged...>,
                     Last,
                     Self<Last, Left...>,
                     Self<Last, Right...>>
    : public MergeUnique<Self<Merged...>, Last, Self<Left...>, Self<Right...>> {
  };

  template <Type... Merged, Type Last, Type... Left, Type... Right>
  struct MergeUnique<Self<Merged...>, Last, Self<Last, Left...>, Self<Right...>>
    : public MergeUnique<Self<Merged...>, Last, Self<Left...>, Self<Right...>> {
  };

  template <Type... Merged, Type Last, Type... Left, Type... Right>
  struct MergeUnique<Self<Merged...>, Last, Self<Left...>, Self<Last, Right...>>
    : public MergeUnique<Self<Merged...>, Last, Self<Left...>, Self<Right...>> {
  };

  template <Type... Merged, Type Last, Type... Left, Type... Right>
  struct MergeUnique<Self<Merged...>, Last, Self<Left...>, Self<Right...>>
    : public MergeImpl<Self<Merged..., Last>, Self<Left...>, Self<Right...>> {};
};

template <class Left, class Right>
using Merge = typename Left::template Merge<Right>::Result;

}  // namespace Seg

#endif  // INCLUDE_SEG_BOX_HPP_
