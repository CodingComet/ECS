#pragma once
#include <tuple>
#include <bitset>
#include <type_traits>

constexpr size_t MAX_COMPONENTS = 32;
using component_signature= std::bitset<MAX_COMPONENTS>;

template <class T, class Tuple>
struct tuple_index;

template <class T, class... Types>
struct tuple_index<T, std::tuple<T, Types...>> {
	static const std::size_t value = 0;
};

template <class T, class U, class... Types>
struct tuple_index<T, std::tuple<U, Types...>> {
	static const std::size_t value = 1 + tuple_index<T, std::tuple<Types...>>::value;
};

template<typename, typename>
struct tuple_holds;

template<typename ...Ts, typename T>
struct tuple_holds<std::tuple<Ts...>, T>
	: std::disjunction<std::is_same<Ts, T>...> {};
