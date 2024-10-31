#pragma once
#include <bitset>
#include <optional>
#include <utility>
#include "common.h"
#include "EntityManager.h"
#include "ComponentManager.h"

class Entity
{
public:
	Entity(EntityManager& entity_manager)
		: entity_manager(entity_manager)
	{
		id = entity_manager.construct_entity();
	}

	~Entity()
	{
		entity_manager.deconstruct_entity(id);
	}

	template <typename T, typename... Args>
	std::optional<T*> get_component(ComponentManager<Args...>& component_manager) const noexcept
	{
		size_t type_id = ComponentManager<Args...>::template get_type_index<T>();

		if (!get_signature()[type_id])
			return std::nullopt;

		return { component_manager.get_component<T>(id) };
	}

	template <typename T, typename...Args>
	std::optional<T*> add_component(ComponentManager<Args...>& component_manager) noexcept
	{
		size_t type_id = ComponentManager<Args...>::template get_type_index<T>();

		if (get_signature()[type_id]) return std::nullopt; // COMPONENT ALREADY EXISTS

		std::optional<T*> result = component_manager.add_component<T>(id);
		if (result.has_value()) entity_manager.set_signature(id, type_id, true);

		return result;
	}

	template <typename T, typename...Args>
	bool remove_component(ComponentManager<Args...>& component_manager) noexcept
	{
		size_t type_id = ComponentManager<Args...>::template get_type_index<T>();

		if (!get_signature()[type_id]) return false; // COMPONENT DOESN'T EXIST

		bool result = component_manager.remove_component<T>(id);
		if (result) entity_manager.set_signature(id, type_id, false);

		return result;
	}

	constexpr component_signature get_signature() const noexcept
	{
		return entity_manager.get_signature(id).value(); // VALUE being bad IS UNREACHABLE
	}

	constexpr size_t get_id() const noexcept
	{
		return id;
	}


private:
	size_t id;
	EntityManager& entity_manager;
};

