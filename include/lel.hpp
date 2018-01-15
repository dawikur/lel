// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_HPP_
#define INCLUDE_LEL_HPP_

#include "lel/lambda.hpp"
#include "lel/operation/binary.hpp"
#include "lel/operation/increment_decrement.hpp"
#include "lel/operation/unary.hpp"
#include "lel/reference.hpp"

template <class IDT, class Compare = std::less<>>
struct lel_t {

using reference = LeL::Reference<Compare, IDT>;

template <IDT ID>
using placeholder = LeL::Lambda<LeL::Context<LeL::Identity>,
                                LeL::Template::Box<Compare, IDT, ID>>;

};

namespace lel {

static constexpr lel_t<char>::reference const _{};

static constexpr lel_t<char>::placeholder<'0'> const _0{};
static constexpr lel_t<char>::placeholder<'1'> const _1{};
static constexpr lel_t<char>::placeholder<'2'> const _2{};
static constexpr lel_t<char>::placeholder<'3'> const _3{};
static constexpr lel_t<char>::placeholder<'4'> const _4{};
static constexpr lel_t<char>::placeholder<'5'> const _5{};
static constexpr lel_t<char>::placeholder<'6'> const _6{};
static constexpr lel_t<char>::placeholder<'7'> const _7{};
static constexpr lel_t<char>::placeholder<'8'> const _8{};
static constexpr lel_t<char>::placeholder<'9'> const _9{};

static constexpr lel_t<char>::placeholder<'a'> const _a{};
static constexpr lel_t<char>::placeholder<'b'> const _b{};
static constexpr lel_t<char>::placeholder<'c'> const _c{};
static constexpr lel_t<char>::placeholder<'d'> const _d{};
static constexpr lel_t<char>::placeholder<'e'> const _e{};
static constexpr lel_t<char>::placeholder<'f'> const _f{};
static constexpr lel_t<char>::placeholder<'g'> const _g{};
static constexpr lel_t<char>::placeholder<'h'> const _h{};
static constexpr lel_t<char>::placeholder<'i'> const _i{};
static constexpr lel_t<char>::placeholder<'j'> const _j{};
static constexpr lel_t<char>::placeholder<'k'> const _k{};
static constexpr lel_t<char>::placeholder<'l'> const _l{};
static constexpr lel_t<char>::placeholder<'m'> const _m{};
static constexpr lel_t<char>::placeholder<'n'> const _n{};
static constexpr lel_t<char>::placeholder<'o'> const _o{};
static constexpr lel_t<char>::placeholder<'p'> const _p{};
static constexpr lel_t<char>::placeholder<'q'> const _q{};
static constexpr lel_t<char>::placeholder<'r'> const _r{};
static constexpr lel_t<char>::placeholder<'s'> const _s{};
static constexpr lel_t<char>::placeholder<'t'> const _t{};
static constexpr lel_t<char>::placeholder<'u'> const _u{};
static constexpr lel_t<char>::placeholder<'v'> const _v{};
static constexpr lel_t<char>::placeholder<'w'> const _w{};
static constexpr lel_t<char>::placeholder<'x'> const _x{};
static constexpr lel_t<char>::placeholder<'y'> const _y{};
static constexpr lel_t<char>::placeholder<'z'> const _z{};

};  // struct lel

#endif  // INCLUDE_LEL_HPP_
