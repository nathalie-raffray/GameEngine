#include "AssetStorage.h"

#include <fstream>
#include <iostream>

#include "Sprite.h"
#include "Animation.h"
#include "AnimationFrame.h"
#include "AnimationCollection.h"
#include "Texture.h"
#include "Asset.h"
//if debug
#include "Game.h"
#include "ImguiWindows.h"

#include "json.hpp"

#include <SFML/Graphics/Texture.hpp>

using json = nlohmann::json;

//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------

AssetStorage::AssetStorage(const std::string& filePath)
{
	json js;
	std::ifstream i(filePath);
	i >> js;

	for (auto& j : js)
	{
		for (auto& jj : j.items())
		{
			table_of_contents.emplace(jj.key(), jj.value());
		}
	}
}

//----------------------------------------------------------------------------------------------

void AssetStorage::load(const AssetId& id)
{
	if (table_of_contents.count(id) == 0)
	{
		std::cout << "Could not load asset with id: " << id << std::endl;
		return;
	}
	std::string filePath = table_of_contents[id];

	json js;
	std::ifstream i(filePath);
	i >> js;

	std::string loadType = js["loadType"];

	if (loadType.compare("animations") == 0) // LOAD ANIMATIONS
	{
		auto uAC = std::make_unique<AnimationCollection>();

		for (json& j : js["animations"])
		{
			auto uA = std::make_unique<Animation>();

			*uA = j;

			uAC->animations.emplace(j["animationId"].get<std::string>(), std::move(uA));
		}

		assets.emplace(js["animationCollectionId"], std::move(uAC));
	}


	else if (loadType.compare("sprites") == 0) // LOAD SPRITES
	{
		for (json& j : js["sprites"])
		{
			auto uS = std::make_unique<Sprite>();

			*uS = j;

			assets.emplace(j["spriteId"].get<std::string>(), std::move(uS));
		}
	}


	else if (loadType.compare("textures") == 0) // LOAD TEXTURES
	{
		for (json& j : js["textures"])
		{
			auto uT = std::make_unique<Texture>();

			assert(uT->texture.loadFromFile(j["filepath"].get<std::string>()));

			assets.emplace(j["texId"].get<std::string>(), std::move(uT));
		}
	}

	else std::cout << "couldn't load asset with load type: " << loadType << std::endl;

}

//----------------------------------------------------------------------------------------------


void AssetStorage::remove(const AssetId& id)
{
	if (assets.count(id) == 0) return;
	assets.erase(id);
}

//----------------------------------------------------------------------------------------------



