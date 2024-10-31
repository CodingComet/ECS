#pragma once
#include <tuple>

template<typename ... Ts>
class SharedState
{
public:
	std::tuple<Ts...> resources;
};

