#include "Entity.h"
#include "EntityRegistry.h"

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

/*void EntityRegistry::remove(EntityHandle h) //ENTITY HANDLE TIENT DANS UN REGISTRE SO NO NEED TO PASS IT BY CONST REF
{
	entities.erase(entities.begin() + h.m_index);
}*/

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
