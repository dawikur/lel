// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_TEMPLATE_SEQUENCE_HPP_
#define INCLUDE_LEL_TEMPLATE_SEQUENCE_HPP_

#include <utility>

namespace LeL {
namespace Template {

template <std::size_t Value, class Result, class Current>
struct Append;

template <std::size_t Value, std::size_t... Current, std::size_t... Count>
struct Append<Value,
              std::index_sequence<Current...>,
              std::index_sequence<Count...>> {
  using Result = std::index_sequence<Current..., (Count - Count + Value)...>;
};

template <std::size_t Max, std::size_t Count, bool Padding>
struct Sequence : Append<Max - 1,
                         std::make_index_sequence<Max>,
                         std::make_index_sequence<Count - Max>> {};

template <std::size_t Max, std::size_t Count>
struct Sequence<Max, Count, false> {
  using Result = std::make_index_sequence<Max>;
};

template <std::size_t Max, std::size_t Count = Max>
using MakeSequence =
  typename Sequence<Max, Count, (Max <= Count && Max != 0)>::Result;

}  // namespace Template
}  // namespace LeL

#endif  // INCLUDE_LEL_TEMPLATE_SEQUENCE_HPP_
