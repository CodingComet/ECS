#pragma once
#include <vector>
#include <unordered_map>
#include <optional>
#include "common.h"

class EntityManager
{
public:
	size_t construct_entity() noexcept;
	void deconstruct_entity(size_t id) noexcept;
	void set_signature(size_t id, size_t index, bool value) noexcept;
	std::optional<component_signature> get_signature(size_t id) const noexcept;

//private:
	size_t current_id = 0;
	std::unordered_map<size_t, component_signature> signatures;
};


size_t EntityManager::construct_entity() noexcept
{
	size_t new_id = current_id++;
	signatures.insert({ new_id, 0 });
	return new_id;
}

void EntityManager::deconstruct_entity(size_t id) noexcept
{
	auto it = signatures.find(id);
	if (it != signatures.end()) signatures.erase(it);
}

std::optional<component_signature> EntityManager::get_signature(size_t id) const noexcept
{
	auto it = signatures.find(id);
	if (it == signatures.end()) return std::nullopt;


	return std::make_optional(it->second);
}

void EntityManager::set_signature(size_t id, size_t index, bool value) noexcept
{
	signatures[id].set(index, value);
}