#include "Game.h"
#include "SystemRegistry.h"
#include "EntityRegistry.h"

void Game::update(float dt)
{
	Game::system_registry->update(dt);
	Game::entity_registry->update();
}
