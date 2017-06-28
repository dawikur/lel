// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_SEG_HPP_
#define INCLUDE_SEG_HPP_

#include <cstddef>
#include <functional>

namespace Seg {

struct Identity {
  template <class Type>
  constexpr auto operator()(Type const &value) const {
    return value;
  }
};

struct Single {};
struct Left {};
struct Right {};
struct Both {};

template <char ID,
          class ViewL = Identity,
          class ViewR = Identity,
          class Impl  = Identity,
          class Mode  = Single>
struct Placeholder {
 public:
  static constexpr char Id = ID;

  constexpr explicit Placeholder() : left(), right() {}

  constexpr explicit Placeholder(ViewL left) : left(std::move(left)), right() {}

  constexpr explicit Placeholder(ViewL left, ViewR right)
    : left(std::move(left)), right(std::move(right)) {}

  template <class Value>
  constexpr auto operator()(Value const &value) const {
    return impl(Mode(), value);
  }

 private:
  template <class Value>
  constexpr auto impl(Single, Value const &value) const {
    return Impl()(left(value));
  }

  template <class Value>
  constexpr auto impl(Left, Value const &value) const {
    return Impl()(left(value), right);
  }

  template <class Value>
  constexpr auto impl(Right, Value const &value) const {
    return Impl()(left, right(value));
  }

  template <class Value>
  constexpr auto impl(Both, Value const &value) const {
    return Impl()(left(value), right(value));
  }

  ViewL const left;
  ViewR const right;

  constexpr auto begin() const {
    placeholder_cannot_be_used_as_a_sequence_you_need_a_view<void>();
  }

  constexpr auto end() const {
    placeholder_cannot_be_used_as_a_sequence_you_need_a_view<void>();
  }

 private:
  template <class>
  constexpr static void
    placeholder_cannot_be_used_as_a_sequence_you_need_a_view() = delete;
};

#define OPERATION(MARK, FUNC)                                                  \
  template <char ID, class... Rest, class Value>                               \
  constexpr auto operator MARK(Placeholder<ID, Rest...> view, Value value)     \
    ->Placeholder<ID, Placeholder<ID, Rest...>, Value, std::FUNC<>, Left> {    \
    return Placeholder<ID,                                                     \
                       Placeholder<ID, Rest...>,                               \
                       Value,                                                  \
                       std::FUNC<>,                                            \
                       Left>(std::move(view), std::move(value));               \
  }                                                                            \
  template <char ID, class... Rest, class Value>                               \
  constexpr auto operator MARK(Value value, Placeholder<ID, Rest...> view)     \
    ->Placeholder<ID, Value, Placeholder<ID, Rest...>, std::FUNC<>, Right> {   \
    return Placeholder<ID,                                                     \
                       Value,                                                  \
                       Placeholder<ID, Rest...>,                               \
                       std::FUNC<>,                                            \
                       Right>(std::move(value), std::move(view));              \
  }                                                                            \
  template <char ID, class... RestL, class... RestR>                           \
  constexpr auto operator MARK(Placeholder<ID, RestL...> viewL,                \
                               Placeholder<ID, RestR...> viewR)                \
    ->Placeholder<ID,                                                          \
                  Placeholder<ID, RestL...>,                                   \
                  Placeholder<ID, RestR...>,                                   \
                  std::FUNC<>,                                                 \
                  Both> {                                                      \
    return Placeholder<ID,                                                     \
                       Placeholder<ID, RestL...>,                              \
                       Placeholder<ID, RestR...>,                              \
                       std::FUNC<>,                                            \
                       Both>(std::move(viewL), std::move(viewR));              \
  }

OPERATION( +  , plus          );
OPERATION( -  , minus         );
OPERATION( *  , multiplies    );
OPERATION( /  , divides       );
OPERATION( %  , modulus       );

OPERATION( == , equal_to      );
OPERATION( != , not_equal_to  );
OPERATION( >  , greater       );
OPERATION( <  , less          );
OPERATION( >= , greater_equal );
OPERATION( <= , less_equal    );

OPERATION( && , logical_and   );
OPERATION( || , logical_or    );

OPERATION( &  , bit_and       );
OPERATION( |  , bit_or        );
OPERATION( ^  , bit_xor       );

#undef OPERATION

#define OPERATION(MARK, FUNC)                                                  \
  template <char ID, class... Rest>                                            \
  constexpr auto operator MARK(Placeholder<ID, Rest...> view)                  \
    ->Placeholder<ID,                                                          \
                  Placeholder<ID, Rest...>,                                    \
                  Identity,                                                    \
                  std::FUNC<>,                                                 \
                  Single> {                                                    \
    return Placeholder<ID,                                                     \
                       Placeholder<ID, Rest...>,                               \
                       Identity,                                               \
                       std::FUNC<>,                                            \
                       Single>(std::move(view));                               \
  }

OPERATION( - , negate      );
OPERATION( ! , logical_not );
OPERATION( ~ , bit_not     );

#undef OPERATION

}  // namespace Seg

#endif  // INCLUDE_SEG_HPP_
