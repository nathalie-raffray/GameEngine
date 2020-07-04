#pragma once
#include <vector>
#include <memory>

/* SYSTEMS */
#include "AnimationSystem.h"
#include "RenderingSystem.h"
#include "GoombaController.h"	
#include "CollisionSystem.h"
#include "Camera.h"
#include "PlayerController.h"

class System;
class SystemRegistry;
struct EntityHandle;

struct SystemHandle
{
	std::size_t m_index;
};

struct SystemRegistryHandle
{
	SystemRegistry* operator->() const;
};

class SystemRegistry
{
public:
	//friend struct SystemHandle;

	template<typename SystemType>
	void add();

	void addEntityToSystems(EntityHandle e);

	//void remove(SystemHandle h);

	void update(float dt);

private:
	std::vector<std::unique_ptr<System>> systems;
	/*  a vector of unique pointers, rather than simple Systems because
		it will be less costly when vector resizes and systems
		are not used sequentially during update() unlike components
		so there won't be the issue of cache misses
	*/
};

template<typename SystemType>
void SystemRegistry::add()
{
	//auto uPtr = std::make_unique<System>(SystemType{});
	//systems.emplace_back(std::move(uPtr));
	systems.emplace_back(new SystemType);
	//	SystemHandle handle{ systems.size() - 1 };
		//return handle; //will move semantics be applied here?
};


