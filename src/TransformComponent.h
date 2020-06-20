#pragma once
#include <SFML/System/Vector2.hpp>

template<typename T>
using Vector2 = sf::Vector2<T>;

struct TransformComponent
{
	Vector2<int> pos;
	float rotationz;
};