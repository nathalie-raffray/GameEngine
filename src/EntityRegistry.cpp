#include "EntityRegistry.h"

EntityHandle EntityRegistry::create()
{
	entities.emplace_back(Entity{});
	EntityHandle handle{ entities.size() - 1 };
	return handle;
	//RETURN STD::MOVE IS DUMB
}

void EntityRegistry::remove(EntityHandle h) //ENTITY HANDLE TIENT DANS UN REGISTRE SO NO NEED TO PASS IT BY CONST REF
{
	entities.erase(entities.begin() + h.m_index);
}

void EntityRegistry::update()
{
	//remove entities that are no longer active
	entities.erase(std::remove_if(std::begin(entities), std::end(entities),
		[](Entity& mEntity)
	{
		return !mEntity.is_active();
	}),
		std::end(entities));
}
