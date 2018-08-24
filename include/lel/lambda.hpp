// Copyright 2017, Dawid Kurek, <dawikur@gmail.com>

#ifndef INCLUDE_LEL_LAMBDA_HPP_
#define INCLUDE_LEL_LAMBDA_HPP_

#include <tuple>

#include "lel/context.hpp"
#include "lel/operator.hpp"
#include "lel/template/variadic.hpp"
#include "lel/wrap.hpp"

namespace LeL {

template <class From, class To>
class Rebind;

template <class Context, class IDs>
class Lambda;

template <class Func, class... Views, class Compare, class IDT, IDT... IDs>
class Lambda<Context<Func, Views...>, Template::Box<Compare, IDT, IDs...>> {
  using ID   = Template::Box<Compare, IDT, IDs...>;
  using This = Lambda<Context<Func, Views...>, ID>;

 public:
  constexpr Lambda(Views... views) : views(std::move(views)...) {}

  template <class... Values>
  constexpr decltype(auto) operator()(Values &&... values) const {
    return call(Template::MakeSequence<sizeof...(Views),
                                       sizeof...(Values)
                                         + sizeof...(Views)
                                         - sizeof...(IDs)
                                       >(),
                std::forward<Values>(values)...);
  }

  constexpr decltype(auto) _() const {
    return Lambda<Context<Operator::Call, This>, ID>{*this};
  }

#define OPERATION(MARK, FUNC)                                                  \
 public:                                                                       \
  template <class... Value>                                                    \
  constexpr decltype(auto) MARK(Value &&... value) const {                     \
    return __##FUNC(typename Rebind<Func, Operator::FUNC>::value{},            \
                    Template::MakeSequence<sizeof...(Views)>(),                \
                    std::forward<Value>(value)...);                            \
  }                                                                            \
                                                                               \
 private:                                                                      \
  /* no_rebind    value    reference */                                        \
  template <class Idx, class... Value>                                         \
  constexpr decltype(auto) __##FUNC(std::false_type, Idx, Value &&... value)   \
    const & {                                                                  \
    return Lambda<Context<Operator::FUNC, This, Wrap<Value const>...>, ID>{    \
      *this, std::forward<Value>(value)...};                                   \
  }                                                                            \
  /*    rebind    value    reference */                                        \
  template <std::size_t... Idx, class... Value>                                \
  constexpr decltype(auto) __##FUNC(                                           \
    std::true_type, std::index_sequence<Idx...>, Value &&... value) const & {  \
    return Lambda<Context<typename Rebind<Func, Operator::FUNC>::type,         \
                          Views...,                                            \
                          Wrap<Value const>...>,                               \
                  ID>{std::get<Idx>(views)..., std::forward<Value>(value)...}; \
  }                                                                            \
                                                                               \
  /* no_rebind    value    reference */                                        \
  template <class Idx, class... RestV, class... IDV>                           \
  constexpr decltype(auto) __##FUNC(                                           \
    std::false_type, Idx, Lambda<RestV, IDV>... view) const & {                \
    return Lambda<Context<Operator::FUNC, This, Lambda<RestV, IDV>...>,        \
                  Template::Merge<ID, IDV...>>{*this, std::move(view)...};     \
  }                                                                            \
  /*    rebind    value    reference */                                        \
  template <std::size_t... Idx, class... RestV, class... IDV>                  \
  constexpr decltype(auto) __##FUNC(                                           \
    std::true_type, std::index_sequence<Idx...>, Lambda<RestV, IDV>... view)   \
    const & {                                                                  \
    return Lambda<Context<typename Rebind<Func, Operator::FUNC>::type,         \
                          Views...,                                            \
                          Lambda<RestV, IDV>...>,                              \
                  Template::Merge<ID, IDV...>>{std::get<Idx>(views)...,        \
                                               std::move(view)...};            \
  }                                                                            \
                                                                               \
  /* no_rebind    value    r-reference */                                      \
  template <class Idx, class... Value>                                         \
  constexpr decltype(auto) __##FUNC(std::false_type, Idx, Value &&... value)   \
    const && {                                                                 \
    return Lambda<Context<Operator::FUNC, This, Wrap<Value const>...>, ID>{    \
      *this, std::forward<Value>(value)...};                                   \
  }                                                                            \
  /*    rebind    value    r-reference */                                      \
  template <std::size_t... Idx, class... Value>                                \
  constexpr decltype(auto) __##FUNC(                                           \
    std::true_type, std::index_sequence<Idx...>, Value &&... value) const && { \
    return Lambda<Context<typename Rebind<Func, Operator::FUNC>::type,         \
                          Views...,                                            \
                          Wrap<Value const>...>,                               \
                  ID>{std::get<Idx>(views)..., std::forward<Value>(value)...}; \
  }                                                                            \
                                                                               \
  /* no_rebind    value    r-reference */                                      \
  template <class Idx, class... RestV, class... IDV>                           \
  constexpr decltype(auto) __##FUNC(                                           \
    std::false_type, Idx, Lambda<RestV, IDV>... view) const && {               \
    return Lambda<Context<Operator::FUNC, This, Lambda<RestV, IDV>...>,        \
                  Template::Merge<ID, IDV...>>{*this, std::move(view)...};     \
  }                                                                            \
  /*    rebind    value    r-reference */                                      \
  template <std::size_t... Idx, class... RestV, class... IDV>                  \
  constexpr decltype(auto) __##FUNC(                                           \
    std::true_type, std::index_sequence<Idx...>, Lambda<RestV, IDV>... view)   \
    const && {                                                                 \
    return Lambda<Context<typename Rebind<Func, Operator::FUNC>::type,         \
                          Views...,                                            \
                          Lambda<RestV, IDV>...>,                              \
                  Template::Merge<ID, IDV...>>{std::get<Idx>(views)...,        \
                                               std::move(view)...};            \
  }

  OPERATION(_, Call)
  OPERATION(operator=, Assign)
  OPERATION(operator[], Subscript)

#undef OPERATION

 private:
  template <class... Values>
  constexpr decltype(auto) call(std::index_sequence<>,
                                Values &&... values) const {
    return Func()(std::forward<Values>(values)...);
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
  constexpr decltype(auto) select(Template::Box<Compare, int, Indexes...>,
                                  Values &&... values) const {
    maybe_unused(std::forward<Values>(values)...);

    return operator()(Template::Variadic::Get<Indexes>::Value(
      std::forward<Values>(values)...)...);
  }

  constexpr decltype(auto) operator()(None const) const { return *this; }

  template <class... Values>
  constexpr static void maybe_unused(Values &&...) {}

  std::tuple<Views...> const views;

  template <class ContextF, class IDsF>
  friend class Lambda;
};

}  // namespace LeL

#endif  // INCLUDE_LEL_LAMBDA_HPP_
