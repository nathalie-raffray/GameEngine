#pragma once
#include <vector>

#include "Game.h"

struct EntityHandle;

class EntityRegistry
{
public:

	~EntityRegistry();
	  
	EntityHandle create();

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
		else {
			return &Game::entity_registry->entities[m_index];
		}
	}

	bool operator<(const EntityHandle& rhs) const
	{
		return (m_index < rhs.m_index);
	}

	uint32_t m_index = INVALID;
};