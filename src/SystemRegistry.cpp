#include "SystemRegistry.h"
#include "System.h"

void SystemRegistry::addEntityToSystems(EntityHandle e)
{
	for (auto& s : systems)
	{
		s->add(e);
	}
}

void SystemRegistry::remove(SystemHandle h)
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
