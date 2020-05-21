#include "Game.h"
#include "SystemRegistry.h"
#include "EntityRegistry.h"
#include "EventManager.h"

void Game::update(float dt)
{
	Game::system_registry->update(dt);
	Game::entity_registry->update(); 
	EventManager::process_events(); //when systems are deleted, their listeners are removed from event manager
}
