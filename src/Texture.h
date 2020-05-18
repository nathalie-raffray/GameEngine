#pragma once

#include <SFML/Graphics/Texture.hpp>
#include "Asset.h"

#include "json.hpp"

using nlohmann::json;

struct Texture : Asset
{
	sf::Texture texture;

	~Texture() override = default;

	static bool load(const std::string& filePath);
};

void from_json(const json& j, Texture& t);
void to_json(json& j, const Texture& t);