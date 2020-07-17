#include "SystemRegistry.h"
#include "System.h"

#include "Game.h"
#include "AssetStorage.h"
#include "Level.h"

//----------------------------------------------------------------------------------------------

void SystemRegistry::addEntityToSystems(EntityHandle e)
{
	for (auto& s : systems)
	{
		s->add(e);
	}
}

//----------------------------------------------------------------------------------------------

void SystemRegistry::update(float dt)
{
	for (auto& s : systems)
	{
		s->refresh();
	}
	for (auto& s : systems)
	{
		s->update(dt);
	}
}

//----------------------------------------------------------------------------------------------

SystemRegistry* SystemRegistryHandle::operator->() const
{
	return &Game::assets->get<Level>(Game::current_level.level_id)->system_registry;
}

//----------------------------------------------------------------------------------------------
