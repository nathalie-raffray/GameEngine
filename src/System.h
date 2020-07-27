#pragma once
#include "Entity.h"
#include "EventManager.h"

struct EntityCompareDefault {
	static bool cmp(const EntityHandle& lhs, const EntityHandle& rhs) {
		return lhs.m_index < rhs.m_index;
	}
};

//template<class Comparator>
class System
{
public:
	//System() : m_entities(std::set<EntityHandle, bool(*)(const EntityHandle&, const EntityHandle&)>(EntityCompareDefault::cmp)) {}

	//template<class Comparator>
	//System(Comparator cmp) : m_entities(std::set<EntityHandle, decltype(cmp)>) {}

	//System(bool(*cmp)(const EntityHandle&, const EntityHandle&)) : m_entities(std::set<EntityHandle, bool(*)(const EntityHandle&, const EntityHandle&)>(cmp)) {}
	//std::set<int, decltype(cmp)*> s(cmp)
	//System() : m_entities(std::set<EntityHandle, std::less<EntityHandle>>()) {}

	//template<class Comparator>
	//System(Comparator cmp) : m_entities(std::set<EntityHandle, Comparator>()) {}

	//System(bool(*cmp)(const EntityHandle&, const EntityHandle&)) : m_entities(std::set<EntityHandle>(cmp)) {}

	virtual ~System() {}
	
	virtual void add(EntityHandle h)
	{
		if (isValid(h))
		{
			m_entities.emplace_back(h);
			init(h);
		}
	}
	virtual void refresh()
	{
		m_entities.erase(std::remove_if(std::begin(m_entities), std::end(m_entities),
			[](EntityHandle h)
			{
				return (!(*h) || !h->m_Active);
			}
			),
			std::end(m_entities));
		/*for (auto& entity : m_entities)
		{
			if (!(*entity) || !entity->m_Active)
			{
				m_entities.erase(entity);
			}
		}*/
	}
	virtual bool isValid(EntityHandle) const = 0;
	
	virtual void init(EntityHandle){}
	
	virtual void update(float) {}

public:

	//std::set<EntityHandle> m_entities;
	std::vector<EntityHandle> m_entities;

};

//using System = TSystem<std::less<EntityHandle>>;

//template class System<std::less<EntityHandle>>;
