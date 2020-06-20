#pragma once

#include "Asset.h"
//#include "EntityRegistry.h"
#include "Entity.h"

#include "json.hpp"

using nlohmann::json;

#include <fstream>
#include "Game.h"
#include "AssetStorage.h"

struct EntityAsset : Asset
{
public: 
	EntityHandle generic_entity;
	//std::string id;

public:
	static bool load(const std::string& filePath)
	{
		json js;
		std::ifstream i(filePath);
		i >> js;

		for (json& j : js["entities"])
		{
			auto uS = std::make_unique<EntityAsset>();

			*uS = j;

			Game::assets->assets.emplace(j["entityId"].get<std::string>(), std::move(uS));
		}
		return true;
	}

};

EntityHandle clone(EntityAsset ea)
{
	EntityHandle eh = Game::entity_registry->create();
	ea.generic_entity->clone(*eh);
	return eh;
}


void to_json(json& j, const EntityAsset& p)
{
	//should there be a to_json?
	//j["entityId"] = p.id;
	//to_json(j, *p.generic_entity);
}
  
void from_json(const json& j, EntityAsset& p)
{
	//p.id = j["entityId"].get<std::string>();

	for (auto& jj : j["components"].items())
	{
		auto& addComponent = ComponentFactory::component_map[jj.key()];
		//do something if this fails, assert
		addComponent(p.generic_entity);

		if (jj.value()["animationCollectionId"])
		{
			p.generic_entity->get<AnimationComponent>()->animation_collection_id = jj.value()["animationCollectionId"];
		}
		if (jj.value()["spriteId"])
		{
			p.generic_entity->get<SpriteComponent>()->spriteId = jj.value()["spriteId"];
		}
	}
}