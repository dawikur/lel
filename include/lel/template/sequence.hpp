// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_TEMPLATE_SEQUENCE_HPP_
#define INCLUDE_LEL_TEMPLATE_SEQUENCE_HPP_

#include <utility>

namespace LeL {
namespace Template {

template <std::size_t Current,
          std::size_t Max,
          std::size_t Count,
          std::size_t... Values>
struct Sequence : std::make_index_sequence<Max> {};

template <std::size_t Max, std::size_t Count = Max>
using MakeSequence = Sequence<0, Max, Count, 0>;

}  // namespace Template
}  // namespace LeL

#endif  // INCLUDE_LEL_TEMPLATE_SEQUENCE_HPP_
