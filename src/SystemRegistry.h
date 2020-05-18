#pragma once
#include <vector>
#include <memory>

//#include "Game.h"
#include "AnimationSystem.h"
#include "RenderingSystem.h"

class System;
struct EntityHandle;

struct SystemHandle
{
	/*Entity* operator->()
	{
		return Game::entity_registry->entities[m_index].get();
	}*/

	std::size_t m_index;
};

class SystemRegistry
{
public:
	//friend struct SystemHandle;

	template<typename SystemType>
	void add();

	void addEntityToSystems(const EntityHandle&& e);

	void remove(const SystemHandle& h);

	void update(float dt);

private:
	std::vector<std::unique_ptr<System>> systems;
	/*  a vector of unique pointers, rather than simple Entities because
		it will be less costly when vector resizes and entities
		are not used sequentially during update() unlike components
		so there won't be the issue of cache misses
	*/
};

template<typename SystemType>
void SystemRegistry::add()
{
	//auto uPtr = std::make_unique<System>(SystemType{});
	//systems.emplace_back(std::move(uPtr));
	systems.emplace_back(std::make_unique<SystemType>());
	SystemHandle handle{ systems.size() - 1 };
	//return handle; //will move semantics be applied here?
}
