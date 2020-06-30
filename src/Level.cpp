#include "Level.h"

#include "json_serialization.h"
#include <fstream>

#include "AssetStorage.h"
#include "Game.h"

#define ADD_SYSTEM(system) if(has_field<std::string>(js["systems"], #system)){ newLevel->system_registry.add<system>(); }

bool Level::load(const std::string& filePath)
{
	json js;
	std::ifstream i(filePath);
	i >> js;

	std::string id = js["id"].get<std::string>();
	//auto uP = std::make_unique<Level>(Level(js["stackable"].get<bool>()));
	auto uP = std::make_unique<Level>();

	Game::assets->assets.emplace(std::make_pair(id, std::move(uP)));
	//Game::assets->assets[id] = std::make_unique<Level>(Level(js["stackable"].get<bool>()));
	//Game::assets->assets[id] = std::make_unique<Asset>(new Level(js["stackable"].get<bool>()));
	auto* newLevel = Game::assets->get<Level>(id);
	Game::current_level = newLevel;
	Game::entity_registry = &newLevel->entity_registry;
	Game::system_registry = &newLevel->system_registry;

	//register systems
	ADD_SYSTEM(AnimationSystem);
	ADD_SYSTEM(GoombaController);
	ADD_SYSTEM(CollisionSystem);
	ADD_SYSTEM(PlayerController);
	ADD_SYSTEM(Camera);
	ADD_SYSTEM(RenderingSystem);

	//add entities
	std::ifstream i2(js.at("entities_filepath").get<std::string>()); 
	json jEntities;
	i2 >> jEntities;
	
	for (json& jEntity : jEntities["entities"])
	{
		auto entity = newLevel->entity_registry.create();
		//Entity& entity = newLevel->entity_registry.entities[handle.m_index];
		**entity = jEntity;
		newLevel->system_registry.addEntityToSystems(entity);
	}

	return true;
}

void Level::pushLevel(const AssetId& levelID)
{
	auto* newLevel = Game::assets->get<Level>(levelID);

	if (!newLevel->stackable)
	{
		if (Level::levels.size() > 0)
		{
			Game::assets->remove(Level::levels.top()); //will call dtors of entityregistry and systemregistry
			Level::levels.pop();
		}
	}

	Level::levels.emplace(levelID);
	Game::current_level = newLevel;
	Game::entity_registry = &newLevel->entity_registry;
	Game::system_registry = &newLevel->system_registry;
}
