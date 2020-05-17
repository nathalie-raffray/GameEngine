#include "EntityRegistry.h"
#include "SystemRegistry.h"
#include "Entity.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"


EntityHandle&& EntityRegistry::create()
{
	entities.emplace_back(std::make_unique<Entity>());
	EntityHandle handle{ entities.size() - 1 };
	Game::system_registry->addEntityToSystems(EntityHandle(handle)); //change this at some point, maybe addEntitytosystems shouldnt take in &&
	return std::move(handle);
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
