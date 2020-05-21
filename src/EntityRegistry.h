#pragma once
#include <vector>

#include "Game.h"
#include "Entity.h"

class EntityRegistry
{
public:
	friend struct EntityHandle;
	  
	EntityHandle create();

	void remove(EntityHandle h);

	void update();

private:
	std::vector<Entity> entities;
	//std::vector<Entity> entities;

	/*  a vector of unique pointers, rather than simple Entities because
		it will be less costly when vector resizes and entities
		are not used sequentially during update() unlike components
		so there won't be the issue of cache misses
	*/
};

struct EntityHandle
{
	Entity* operator->() const
	{
		if (!Game::entity_registry->entities[m_index].is_active())
		{
			return nullptr;
		}
		else {
			return &Game::entity_registry->entities[m_index];
		}
	}

	std::size_t m_index;
};