#pragma once
#include <tuple>
#include <variant>


template<typename ... Ts>
class StateMachine
{
public:
	std::tuple<Ts...> states;
	std::variant<Ts*...> state;
};

