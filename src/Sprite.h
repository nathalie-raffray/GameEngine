#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include <string>

#include "json_serialization.h"

#include "Asset.h"

using TextureId = std::string;
using IntRect = sf::IntRect;
using FloatRect = sf::FloatRect;

struct EntityHandle;

struct Sprite : Asset
{
	TextureId texId;
	IntRect texRect;

	sf::Sprite m_sprite;

	static FloatRect getBounds(EntityHandle eh);

	~Sprite() override = default;

	static bool load(const std::string& filePath);

};

void to_json(json& j, const Sprite& p);
void from_json(const json& j, Sprite& p);

