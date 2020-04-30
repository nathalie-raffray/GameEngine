#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include <string>

#include "json.hpp"

using nlohmann::json;

using TextureId = std::string;
using IntRect = sf::IntRect;

struct Sprite
{
	TextureId texId;
	IntRect texRect;
	//float scale; //this can eventually be stored in a transform

	sf::Sprite m_sprite;
};

void to_json(json& j, const Sprite& p);
void from_json(const json& j, Sprite& p);

void to_json(json& j, const IntRect& p);
void from_json(const json& j, IntRect& p);