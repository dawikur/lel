// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_HPP_
#define INCLUDE_LEL_HPP_

#include "lel/operation.hpp"
#include "lel/reference.hpp"

namespace LeL {

using IDT = char;

template <IDT ID>
using Placeholder = Lambda<Context<Identity>, Box<IDT, ID>>;

namespace Placeholders {

static constexpr Reference<IDT> const _{};

static constexpr Placeholder<'0'> const _0;
static constexpr Placeholder<'1'> const _1;
static constexpr Placeholder<'2'> const _2;
static constexpr Placeholder<'3'> const _3;
static constexpr Placeholder<'4'> const _4;
static constexpr Placeholder<'5'> const _5;
static constexpr Placeholder<'6'> const _6;
static constexpr Placeholder<'7'> const _7;
static constexpr Placeholder<'8'> const _8;
static constexpr Placeholder<'9'> const _9;

static constexpr Placeholder<'a'> const _a;
static constexpr Placeholder<'b'> const _b;
static constexpr Placeholder<'c'> const _c;
static constexpr Placeholder<'d'> const _d;
static constexpr Placeholder<'e'> const _e;
static constexpr Placeholder<'f'> const _f;
static constexpr Placeholder<'g'> const _g;
static constexpr Placeholder<'h'> const _h;
static constexpr Placeholder<'i'> const _i;
static constexpr Placeholder<'j'> const _j;
static constexpr Placeholder<'k'> const _k;
static constexpr Placeholder<'l'> const _l;
static constexpr Placeholder<'m'> const _m;
static constexpr Placeholder<'n'> const _n;
static constexpr Placeholder<'o'> const _o;
static constexpr Placeholder<'p'> const _p;
static constexpr Placeholder<'q'> const _q;
static constexpr Placeholder<'r'> const _r;
static constexpr Placeholder<'s'> const _s;
static constexpr Placeholder<'t'> const _t;
static constexpr Placeholder<'u'> const _u;
static constexpr Placeholder<'v'> const _v;
static constexpr Placeholder<'w'> const _w;
static constexpr Placeholder<'x'> const _x;
static constexpr Placeholder<'y'> const _y;
static constexpr Placeholder<'z'> const _z;

}  // namespace Placeholders

}  // namespace LeL

#endif  // INCLUDE_LEL_HPP_
