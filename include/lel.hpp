// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_HPP_
#define INCLUDE_LEL_HPP_

#include "lel/operation.hpp"

namespace LeL {

template <char ID>
using Placeholder = Impl<Context<>, Box<char, ID>>;

namespace Placeholders {

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

static constexpr Placeholder<'A'> const _A;
static constexpr Placeholder<'B'> const _B;
static constexpr Placeholder<'C'> const _C;
static constexpr Placeholder<'D'> const _D;
static constexpr Placeholder<'E'> const _E;
static constexpr Placeholder<'F'> const _F;
static constexpr Placeholder<'G'> const _G;
static constexpr Placeholder<'H'> const _H;
static constexpr Placeholder<'I'> const _I;
static constexpr Placeholder<'J'> const _J;
static constexpr Placeholder<'K'> const _K;
static constexpr Placeholder<'L'> const _L;
static constexpr Placeholder<'M'> const _M;
static constexpr Placeholder<'N'> const _N;
static constexpr Placeholder<'O'> const _O;
static constexpr Placeholder<'P'> const _P;
static constexpr Placeholder<'Q'> const _Q;
static constexpr Placeholder<'R'> const _R;
static constexpr Placeholder<'S'> const _S;
static constexpr Placeholder<'T'> const _T;
static constexpr Placeholder<'U'> const _U;
static constexpr Placeholder<'V'> const _V;
static constexpr Placeholder<'W'> const _W;
static constexpr Placeholder<'X'> const _X;
static constexpr Placeholder<'Y'> const _Y;
static constexpr Placeholder<'Z'> const _Z;

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
