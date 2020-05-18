#include "Texture.h"
#include "Game.h"
#include "AssetStorage.h"
#include <fstream>

/*
void from_json(const json& j, Texture& t)
{

}

void to_json(json& j, const Texture& t)
{
}
*/

bool Texture::load(const std::string& filePath)
{
	json js;
	std::ifstream i(filePath);
	i >> js;

	for (json& j : js["textures"])
	{
		auto uT = std::make_unique<Texture>();

		assert(uT->texture.loadFromFile(j["filepath"].get<std::string>()));

		Game::assets->assets.emplace(j["texId"].get<std::string>(), std::move(uT));
	}
	
	return true;
}
