#pragma once
#include <stack>
#include <vector>
#include <unordered_map>

template<typename T>
class ComponentPool
{
public:
	ComponentPool()
	{}

	std::optional<T*> get_component(size_t index) noexcept
	{
		auto it = index_to_index_map.find(index);
		if (it == index_to_index_map.end()) return std::nullopt;
		return { &data[it->second] };
	}

	std::optional<T*> add_component(size_t index) noexcept
	{
		auto it = index_to_index_map.find(index);
		if (it != index_to_index_map.end()) return std::nullopt;
		if (holes.empty())
		{
			index_to_index_map.insert({ index, data.size() });
			data.emplace_back();
			return { &data.back() };
		}

		size_t hole = holes.top(); holes.pop();
		index_to_index_map.insert({ index, hole });
		data[hole] = T();

		return { &data[hole] };
	}

	bool remove_component(size_t index) noexcept
	{
		auto it = index_to_index_map.find(index);
		if (it == index_to_index_map.end()) return false;

		data[it->second] = T();
		holes.push(it->second);
		index_to_index_map.erase(it);

		return true;
	}

private:
	std::vector<T> data;
	std::stack<size_t> holes;
	std::unordered_map<size_t, size_t> index_to_index_map;
};
