#pragma once

#include <tuple>
#include "common.h"
#include "ComponentPool.h"

template <typename ... Args>
class ComponentManager
{
public:
	using data_t = std::tuple<ComponentPool<Args>...>;
	using data_types = std::tuple<Args...>;

	ComponentManager() {}
	~ComponentManager() {}

	template <typename T>
	static consteval size_t get_type_index()
	{
		static_assert(tuple_holds<data_types, T>());

		return tuple_index<T, data_types>::value;
	}

	template <typename T>
	std::optional<T*> get_component(size_t index) noexcept
	{
		return std::get<ComponentPool<T>>(data).get_component(index);
	}

	template <typename T>
	std::optional<T*> add_component(size_t id) noexcept
	{
		return std::get<ComponentPool<T>>(data).add_component(id);
	}

	template <typename T>
	bool remove_component(size_t id) noexcept
	{
		return std::get<ComponentPool<T>>(data).remove_component(id);
	}


private:
	data_t data;
};

