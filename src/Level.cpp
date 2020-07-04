#include "Level.h"

#include <fstream>

#include "AssetStorage.h"
#include "Game.h"

#define ADD_SYSTEM(system) if(has_field<std::string>(js["systems"], #system)){ Game::system_registry->add<system>(); }

bool Level::load(const std::string& filePath)
{
	json js;
	std::ifstream i(filePath);
	i >> js;

	std::string id = js["id"].get<std::string>();

	auto uP = std::make_unique<Level>();
	Game::assets->assets.emplace(std::make_pair(id, std::move(uP)));

	Game::current_level = { id };
	//*Game::current_level = js;

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
		auto entity = Game::entity_registry->create();
		//Entity& entity = newLevel->entity_registry.entities[handle.m_index];
		**entity = jEntity;
		if (entity->has<CameraComponent>())
		{
			Game::current_level->camera = entity;
		}
		Game::system_registry->addEntityToSystems(entity);
	}
	return true;
}

void Level::pushLevel(LevelHandle level)
{
	if (!level->stackable)
	{
		if (Level::levels.size() > 0)
		{
			Game::assets->remove(Level::levels.top().level_id); //will call dtors of entityregistry and systemregistry
			Level::levels.pop();
		}
	}

	Level::levels.emplace(level);
	Game::current_level = level;
}

void from_json(const json& js, Level& l)
{
	//l.system_registry.add<AnimationSystem>();
	
	//register systems
	/*ADD_SYSTEM(AnimationSystem);
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
		auto entity = l.entity_registry.create();
		//Entity& entity = newLevel->entity_registry.entities[handle.m_index];
		**entity = jEntity;
		l.system_registry.addEntityToSystems(entity);
	}*/
}

void to_json(json& j, const Level& l)
{

}

Level* LevelHandle::operator->() const
{
	return Game::assets->get<Level>(level_id);
}

Level& LevelHandle::operator*() const
{
	return *Game::assets->get<Level>(level_id);
}
