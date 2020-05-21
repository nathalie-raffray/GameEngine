#pragma once
#include "EntityRegistry.h"

class System
{
public:
	virtual ~System() {}
	
	void add(EntityHandle h)
	{
		if (isValid(h))
		{
			m_entities.emplace_back(h);
			onAdded(h);
		}
	}
	virtual void refresh()
	{
		m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities),
			[](EntityHandle h)
		{
			return !h->is_active();
		}),
			std::end(m_entities));
	}
	virtual bool isValid(EntityHandle) const = 0;
	
	virtual void onAdded(EntityHandle){}
	
	virtual void update(float) {}

protected:
	std::vector<EntityHandle> m_entities;

};
