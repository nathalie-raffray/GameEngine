#include "EntityRegistry.h"
#include "SystemRegistry.h"
#include "Entity.h"

#include "ImguiWindows.h"//TEMPORARY
void EntityRegistry::add(Entity&& entity)
{
	entities.emplace_back(std::make_unique<Entity>(entity));
	EntityHandle handle{ entities.size() - 1 };
	Game::imguiWin->add(handle); //TEMPORARY UNTIL I MAKE IMGUI WINDOWS AN OFFICIAL SYSTEM 
	Game::system_registry->addEntityToSystems(std::move(handle));
}

void EntityRegistry::remove(const EntityHandle& h)
{
	entities.erase(entities.begin() + h.m_index);
}

void EntityRegistry::update()
{
	//remove entities that are no longer active
	entities.erase(std::remove_if(std::begin(entities), std::end(entities),
		[](const std::unique_ptr<Entity>& mEntity)
	{
		return !mEntity->is_active();
	}),
		std::end(entities));
}
