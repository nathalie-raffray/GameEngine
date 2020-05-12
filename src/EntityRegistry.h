#pragma once
#include <vector>
#include <memory>

#include "Game.h"

template<typename... ComponentTypes>
class CEntity;
struct EntityHandle;

struct AnimationComponent;
struct SpriteComponent;
using Entity = CEntity<AnimationComponent, SpriteComponent>;

class EntityRegistry
{
public:
	friend struct EntityHandle;
	  
	void add(Entity&& entity);

	void remove(const EntityHandle& h);

	void update();

private:
	std::vector<std::unique_ptr<Entity>> entities;
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
		return Game::entity_registry->entities[m_index].get();
	}

	std::size_t m_index;
};