#include "Entity.h"
#include "Level.h"
#include "AssetStorage.h"

EntityRegistry::~EntityRegistry()
{
	for (auto& entity : entities)
	{
		entity.destroy();
	}
	entities.clear();
}

EntityHandle EntityRegistry::create()
{
	entities.emplace_back(Entity{});
	EntityHandle handle{ static_cast<uint32_t>(entities.size()) - 1 };
	return handle;
	//RETURN STD::MOVE IS DUMB
}

void EntityRegistry::update()
{
	//remove entities that are no longer active
	entities.erase(std::remove_if(std::begin(entities), std::end(entities),
		[](Entity& mEntity)
	{
		if (!mEntity.is_active())
		{
			mEntity.destroy(); //cant allow erase() to call destructor because if in destructor I remove all components (and allocate freeIndices) then when entities resizes it will also call destructor and fuck up freeIndices
			return true;
		}
		return false;
	}),
		std::end(entities));
}

EntityRegistry* EntityRegistryHandle::operator->() const
{
	return &Game::assets->get<Level>(Game::current_level.level_id)->entity_registry;
}
