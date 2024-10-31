#pragma once
#include <set>
#include <tuple>
#include <ranges>
#include <algorithm>
#include <functional>

#include "common.h"
#include "Entity.h"


namespace rv = std::ranges::views;

constexpr bool operator<(const Entity& lhs, const Entity& rhs) {
	return lhs.get_id() < rhs.get_id();
}


template<typename _ComponentManager, typename _SharedState, typename ... Ts>
class System
{
public:
	System(std::function<void(_SharedState&, Ts&
		...)> fn)
		: fn(fn)
	{
		// ASSERT IF EVERY T IS IN COMPONENT MANAGER
		(signature.set(_ComponentManager::template get_type_index<Ts>()), ...);
	}

	void execute(_ComponentManager& component_manager, _SharedState& shared_state)
	{
		std::ranges::for_each(ids, [=, &component_manager, &shared_state](const auto& id) {fn(shared_state, *component_manager.get_component<Ts>(id).value() ...); });
	}



	constexpr auto match_signature(const EntityManager& entity_manager) const
	{
		return [s = signature, entity_manager](const size_t& id) {return (entity_manager.get_signature(id).value_or(0) & s) == s; }; // SHOULD NOT GET OR CASE EVER
	}

	void filter_entities(const EntityManager& entity_manager)
	{
		ids.clear();
		std::ranges::copy(rv::keys(entity_manager.signatures)
			| rv::filter(match_signature(entity_manager)),
			std::inserter(ids, ids.begin()));
	}

	//bool try_add_entity(const Entity& entity)
	//{
	//	if (!match_signature()(entity)) return false;

	//	ids.insert(entity.get_id());
	//	return true;
	//}

	//bool try_remove_entity(const Entity& entity)
	//{
	//	if (ids.find(entity.get_id()) == ids.end()) return false;

	//	ids.erase(entity.get_id());
	//	return true;
	//}

	//void entity_changed(const Entity& entity)
	//{
	//	try_remove_entity(entity);
	//	try_add_entity(entity);
	//}


private:
	component_signature signature;
	std::set<size_t> ids; // should probobaly use some tree type(ordered?) and only update one at a time - std::set?
	std::function<void(_SharedState&, Ts&...)> fn;
};