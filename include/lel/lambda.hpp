// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_LAMBDA_HPP_
#define INCLUDE_LEL_LAMBDA_HPP_

#include <tuple>

#include "lel/template/sequence.hpp"
#include "lel/template/variadic.hpp"
#include "lel/context.hpp"
#include "lel/functor.hpp"
#include "lel/wrap.hpp"

namespace LeL {

template <class Context, class IDs>
class Lambda;

template <class Func, class... Views, class IDT, IDT... IDs>
class Lambda<Context<Func, Views...>, Template::Box<IDT, IDs...>> {
  using ID    = Template::Box<IDT, IDs...>;
  using Class = Lambda<Context<Func, Views...>, ID>;

 public:
  constexpr Lambda(Views... views) : views(std::move(views)...) {}

  template <class... Values>
  constexpr decltype(auto) operator()(Values &&... values) const {
    return call(std::index_sequence_for<Views...>(),
                std::forward<Values>(values)...);
  }

#define OPERATION(MARK, FUNC)                                                  \
  template <class... Value>                                                    \
  constexpr decltype(auto) MARK(Value &&... value) const {                     \
    return Lambda<Context<FUNC, Class, Wrap<Value const>...>, ID>{             \
      *this, std::forward<Value>(value)...};                                   \
  }                                                                            \
  template <class... RestV, class... IDV>                                      \
  constexpr decltype(auto) MARK(Lambda<RestV, IDV>... view) const {            \
    return Lambda<Context<FUNC, Class, Lambda<RestV, IDV>...>,                 \
                  Template::Merge<ID, IDV...>>{*this, std::move(view)...};     \
  }

  constexpr decltype(auto) _() const {
    return Lambda<Context<Call, Class>, ID>{*this};
  }

  OPERATION(_, Call)
  OPERATION(operator=, Assign)
  OPERATION(operator[], Subscript)

#undef OPERATION

 private:
  template <class... Values>
  constexpr decltype(auto) call(std::index_sequence<>,
                                Values &&... values) const {
    return Func()(std::forward<Values>(std::forward<Values>(values))...);
  }

  template <std::size_t... Idx, class... Values>
  constexpr decltype(auto) call(std::index_sequence<Idx...>,
                                Values &&... values) const {
    return Func()(
      std::get<Idx>(views).slice(ID(), std::forward<Values>(values)...)...);
  }

  template <class Slice, class... Values>
  constexpr decltype(auto) slice(Slice, Values &&... values) const {
    using Indexes = typename Slice::template IndexesOf<IDs...>;

    return select(Indexes(), std::forward<Values>(values)...);
  }

  template <int... Indexes, class... Values>
  constexpr decltype(auto) select(Template::Box<int, Indexes...>,
                                  Values &&... values) const {
    return operator()(Template::Variadic::Get<Indexes>::Value(
      std::forward<Values>(values)...)...);
  }

  constexpr decltype(auto) operator()(None const) const { return *this; }

  std::tuple<Views...> const views;

  template <class ContextF, class IDsF>
  friend class Lambda;
};

}  // namespace LeL

#endif  // INCLUDE_LEL_LAMBDA_HPP_
