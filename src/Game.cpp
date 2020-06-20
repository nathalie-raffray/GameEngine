#include "Game.h"
#include "SystemRegistry.h"
//#include "EntityRegistry.h"
#include "Entity.h"
#include "EventManager.h"
#include "ActionSystem.h"

void Game::init()
{
	//register systems
	system_registry->add<AnimationSystem>();
	system_registry->add<GoombaController>();
	system_registry->add<CollisionSystem>();
	system_registry->add<PlayerController>();
	system_registry->add<Camera>();
	system_registry->add<RenderingSystem>();

	ActionSystem::init("../res/data/inputconfig.json");
	ComponentFactory::init();
}

void Game::update(float dt)
{
	system_registry->update(dt);
	entity_registry->update(); 
	EventManager::process_events(); //when systems are deleted, their listeners are removed from event manager
}
