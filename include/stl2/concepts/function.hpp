#ifndef STL2_CONCEPTS_FUNCTION_HPP
#define STL2_CONCEPTS_FUNCTION_HPP

#include <stl2/concepts/compare.hpp>
#include <stl2/concepts/core.hpp>
#include <stl2/concepts/object.hpp>

#include <type_traits>

////////////////////////////////////////////
// Function Concepts [concepts.lib.function]
//
namespace stl2 { inline namespace v1 {

template <class F, class...Args>
using ResultType =
  std::result_of_t<F(Args...)>;

template <class F, class...Args>
concept bool Function() {
  return CopyConstructible<F>() &&
    requires (F& f, Args&&...args) {
      typename ResultType<F, Args...>;
      f((Args&&)(args)...);
      requires Same<ResultType<F, Args...>,
                    decltype(f(stl2::forward<Args>(args)...))>();
    };
}

template <class F, class...Args>
concept bool RegularFunction() {
  return Function<F, Args...>();
}

template <class F, class...Args>
concept bool Predicate() {
  return RegularFunction<F, Args...> &&
    Boolean<ResultType<F, Args...>>();
}

template <class R, class T, class U = T>
concept bool Relation() {
  return Predicate<R, T, T>() &&
    (Same<T, U>() ||
      (Predicate<R, T, U>() &&
       Predicate<R, U, T>() &&
       Predicate<R, U, U>()));
}

template <class R, class T, class U = T>
concept bool StrongRelation() {
  return Relation<R, T, U>() &&
    (Same<T, U>() ||
      (Common<T, U>() &&
       Predicate<R, CommonType<T, U>, CommonType<T, U>>()));

template <class R, class T, class U = T>
concept bool StrictWeakOrder() {
  return Relation<R, T, U>();
}

}} // namespace stl2::v1

#endif // STL2_CONCEPTS_FUNCTION_HPP
