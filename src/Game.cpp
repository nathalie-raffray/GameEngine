#include "Game.h"
#include "SystemRegistry.h"
#include "Entity.h"
#include "EventManager.h"
#include "ActionSystem.h"
#include "Level.h"
#include "AssetStorage.h"

void Game::init(const std::string& level)
{
	//register systems
	/*system_registry->add<AnimationSystem>();
	system_registry->add<GoombaController>();
	system_registry->add<CollisionSystem>();
	system_registry->add<PlayerController>();
	system_registry->add<Camera>();
	system_registry->add<RenderingSystem>();*/

	//current_level = Game::assets->get<Level>(level);
	Level::pushLevel(level);
	ActionSystem::init("../res/data/inputconfig.json");
	ComponentFactory::init();
}

void Game::update(float dt)
{
	system_registry->update(dt);
	entity_registry->update(); 
	EventManager::process_events(); //when systems are deleted, their listeners are removed from event manager
}
