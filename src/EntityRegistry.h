#pragma once
#include <vector>

#include "Game.h"

struct EntityHandle;

class EntityRegistry
{
public:
	//friend struct EntityHandle;
	//friend class Level;

	~EntityRegistry();
	  
	EntityHandle create();

	//void remove(EntityHandle h);

	void update();

	std::vector<Entity> entities;
};

struct EntityRegistryHandle
{
	EntityRegistry* operator->() const;
};

struct EntityHandle
{
	Entity* operator->() const
	{
		if (m_index == INVALID)
		{
			return nullptr;
		}
		/*if (!Game::entity_registry->entities[m_index].is_active())
		{
			return nullptr;
		}*/
		else {
			return &Game::entity_registry->entities[m_index];
		}
	}

	Entity* operator*() const
	{
		if (m_index == INVALID)
		{
			return nullptr;
		}
		/*else if (!Game::entity_registry->entities[m_index].is_active())
		{
			return nullptr;
		}*/
		else {
			return &Game::entity_registry->entities[m_index];
		}
	}

	uint32_t m_index = INVALID;
	//instead of size_t
};