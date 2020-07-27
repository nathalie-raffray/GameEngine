#pragma once

#include <SFML/Graphics/Texture.hpp>
#include "Asset.h"

struct Texture : Asset
{
	sf::Texture texture;

	~Texture() override = default;

	static bool load(const std::string& filePath);
};
