#pragma once
#include <SFML/System/Vector2.hpp>

template<typename T>
using Vector2 = sf::Vector2<T>;
//koopa paratroopa and flying goomba hops
struct HopComponent
{
	Vector2<int> hop_bounds; //hop width and height
	//might be useful for mario as well. to calculate jump position. 
};