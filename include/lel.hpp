// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_HPP_
#define INCLUDE_LEL_HPP_

#include <functional>

#include "lel/lambda.hpp"
#include "lel/operator/binary.hpp"
#include "lel/operator/increment_decrement.hpp"
#include "lel/operator/unary.hpp"
#include "lel/reference.hpp"

template <class IDT, class Compare = std::less<>>
struct lel_t {

using reference = LeL::Reference<Compare, IDT>;

template <IDT ID>
using placeholder = LeL::Lambda<LeL::Context<LeL::Operator::Identity>,
                                LeL::Template::Box<Compare, IDT, ID>>;

};

namespace lel {

using reference = lel_t<char>::reference;

template <char ID>
using placeholder = lel_t<char>::placeholder<ID>;

static constexpr reference const _{};

static constexpr placeholder<'0'> const _0{};
static constexpr placeholder<'1'> const _1{};
static constexpr placeholder<'2'> const _2{};
static constexpr placeholder<'3'> const _3{};
static constexpr placeholder<'4'> const _4{};
static constexpr placeholder<'5'> const _5{};
static constexpr placeholder<'6'> const _6{};
static constexpr placeholder<'7'> const _7{};
static constexpr placeholder<'8'> const _8{};
static constexpr placeholder<'9'> const _9{};

static constexpr placeholder<'a'> const _a{};
static constexpr placeholder<'b'> const _b{};
static constexpr placeholder<'c'> const _c{};
static constexpr placeholder<'d'> const _d{};
static constexpr placeholder<'e'> const _e{};
static constexpr placeholder<'f'> const _f{};
static constexpr placeholder<'g'> const _g{};
static constexpr placeholder<'h'> const _h{};
static constexpr placeholder<'i'> const _i{};
static constexpr placeholder<'j'> const _j{};
static constexpr placeholder<'k'> const _k{};
static constexpr placeholder<'l'> const _l{};
static constexpr placeholder<'m'> const _m{};
static constexpr placeholder<'n'> const _n{};
static constexpr placeholder<'o'> const _o{};
static constexpr placeholder<'p'> const _p{};
static constexpr placeholder<'q'> const _q{};
static constexpr placeholder<'r'> const _r{};
static constexpr placeholder<'s'> const _s{};
static constexpr placeholder<'t'> const _t{};
static constexpr placeholder<'u'> const _u{};
static constexpr placeholder<'v'> const _v{};
static constexpr placeholder<'w'> const _w{};
static constexpr placeholder<'x'> const _x{};
static constexpr placeholder<'y'> const _y{};
static constexpr placeholder<'z'> const _z{};

}  // namespace lel

#endif  // INCLUDE_LEL_HPP_
