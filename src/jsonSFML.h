#pragma once
#include <SFML/Graphics/Rect.hpp>

using IntRect = sf::IntRect;

template<typename T>
using Vector2 = sf::Vector2<T>;

namespace sf
{
	void to_json(json& j, const IntRect& p);
	void from_json(const json& j, IntRect& p);

	template<typename T>
	void to_json(json& j, const Vector2<T>& p);

	template<typename T>
	void to_json(json& j, const Vector2<T>& p)
	{
		j = json{ p.x, p.y };
	}
	template<typename T>
	void from_json(const json& j, Vector2<T>& p) 
	{
		p.x = j[0].get<T>();
		p.y = j[1].get<T>();
	}
	
}
