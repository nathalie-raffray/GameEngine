#pragma once
#include <SFML/Graphics/Rect.hpp>

#include "json.hpp"

using nlohmann::json;

using IntRect = sf::IntRect;

namespace sf
{
	void to_json(json& j, const IntRect& p);
	void from_json(const json& j, IntRect& p);
}
