#pragma once
#include "EntityRegistry.h"
#include "Entity.h" //include this for every system?

class System
{
public:
	virtual void add(const EntityHandle h)
	{
		if (isValid(h)) m_entities.emplace_back(h);
	}
	virtual void refresh()
	{
		m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities),
			[](const EntityHandle& h)
		{
			return !h->is_active();
		}),
			std::end(m_entities));
	}
	virtual bool isValid(const EntityHandle& h) = 0;
	virtual void update(float dt) = 0;

protected:
	std::vector<EntityHandle> m_entities;

};
