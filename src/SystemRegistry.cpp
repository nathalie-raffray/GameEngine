#include "SystemRegistry.h"
#include "System.h"
#include "AnimationSystem.h"
#include "RenderingSystem.h"

void SystemRegistry::addEntityToSystems(const EntityHandle&& e)
{
	for (auto& s : systems)
	{
		s->add(e);
	}
}

void SystemRegistry::remove(const SystemHandle& h)
{
	systems.erase(systems.begin() + h.m_index);
}

void SystemRegistry::update(float dt)
{
	for (auto& s : systems)
	{
		s->update(dt);
	}
	for (auto& s : systems)
	{
		s->refresh();
	}
}
