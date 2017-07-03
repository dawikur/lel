# lel

> Lambda Expression Library
> > Single header (after fusing) library with no external dependencies.

[![Language][Language-img]][Language-url]
[![Release][Release-img]][Release-url]
[![License][License-img]][License-url]

[![Master][Master-img]][Master-url]
[![MasterLinuxBuild][MasterLinuxBuild-img]][MasterLinuxBuild-url]
[![MasterWindowsBuild][MasterWindowsBuild-img]][MasterWindowsBuild-url]
[![MasterCoverage][MasterCoverage-img]][MasterCoverage-url]
[![MasterCodeClimate][MasterCodeClimate-img]][MasterCodeClimate-url]

[![Develop][Develop-img]][Develop-url]
[![DevelopLinuxBuild][DevelopLinuxBuild-img]][DevelopLinuxBuild-url]
[![DevelopWindowsBuild][DevelopWindowsBuild-img]][DevelopWindowsBuild-url]
[![DevelopCoverage][DevelopCoverage-img]][DevelopCoverage-url]

---

```cpp
auto is_right_triangle = _a * _a + _b *_b == _c * _c;

is_right_triangle(3, 4, 5);
```

# About

Lambda functions in c++ are cool, very cool. But they give quite some overhead
in syntax requirements, which obscures very little functions. Consider:

```cpp
auto is_even = [](auto i) { return i % 2 == 0; };
```

It is very short, nice lambda, but the actual condition is only around half of
its body. Now lets see how it would look in lambda expression:

```cpp
auto is_even = _x % 2 == 0;
```

Shorted, right? And, for me, much cleaner.

## Boost Lambda Library?

Yes, the same concept but this one uses a little bit newer C++.
LeL also does not constrain maximum number of arguments to 3.

# Examples

```cpp

// simple
auto plus_one = _x + 1;
auto multiply = _x * _y;
auto is_less  = _1 < _2;

// more arguments
auto compute_something = 1 + _x * 3 - _y * _y + _x * _z;

// make own placeholders
auto first_arg  = Lel::Placeholder<'1'>();
auto second_arg = Lel::Placeholder<'2'>();

auto not_equal = first_arg != second_arg;

// some more... complex...

auto sum = *((*_x)[_1]) + **(_y[_2]);

auto x = std::make_unique<std::vector<std::unique_ptr<int>>>();
std::unique_ptr<std::vector<std::unique_ptr<int>>> x = ...;
std::vector<std::unique_ptr<std::unique_ptr<int>>> y = ...;

ASSERT_EQ(3 + 9, sum(2, 3, x, y));
```

---

[Language-img]: https://img.shields.io/badge/language-C++14-d65d0e.svg?style=flat-square
[Language-url]: https://isocpp.org
[Release-img]: https://img.shields.io/github/release/dawikur/lel.svg?style=flat-square
[Release-url]: https://github.com/dawikur/lel/releases
[License-img]: https://img.shields.io/github/license/dawikur/lel.svg?style=flat-square
[License-url]: https://github.com/dawikur/lel/blob/master/LICENSE

[Master-img]: https://img.shields.io/badge/-%20master-grey.svg?style=flat-square
[Master-url]: https://github.com/dawikur/lel
[MasterLinuxBuild-img]: https://img.shields.io/travis/dawikur/lel/master.svg?label=linux&style=flat-square
[MasterLinuxBuild-url]: https://travis-ci.org/dawikur/lel
[MasterWindowsBuild-img]: https://img.shields.io/appveyor/ci/dawikur/lel/master.svg?label=windows&style=flat-square
[MasterWindowsBuild-url]: https://ci.appveyor.com/project/dawikur/lel
[MasterCoverage-img]: https://img.shields.io/codecov/c/github/dawikur/lel/master.svg?label=coverage&style=flat-square
[MasterCoverage-url]: https://codecov.io/gh/dawikur/lel
[MasterCodeClimate-img]: https://img.shields.io/codeclimate/github/dawikur/lel.svg?style=flat-square
[MasterCodeClimate-url]: https://codeclimate.com/github/dawikur/lel/

[Develop-img]: https://img.shields.io/badge/-develop-lightgrey.svg?style=flat-square
[Develop-url]: https://github.com/dawikur/lel/tree/develop
[DevelopLinuxBuild-img]: https://img.shields.io/travis/dawikur/lel/develop.svg?label=linux&style=flat-square
[DevelopLinuxBuild-url]: https://travis-ci.org/dawikur/lel
[DevelopWindowsBuild-img]: https://img.shields.io/appveyor/ci/dawikur/lel/develop.svg?label=windows&style=flat-square
[DevelopWindowsBuild-url]: https://ci.appveyor.com/project/dawikur/lel
[DevelopCoverage-img]: https://img.shields.io/codecov/c/github/dawikur/lel/develop.svg?label=coverage&style=flat-square
[DevelopCoverage-url]: https://codecov.io/gh/dawikur/lel
