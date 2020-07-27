#pragma once
#include "Entity.h"
#include "SideEnum.h"

struct collision
{
	EntityHandle collider1;
	EntityHandle collider2;

	side collision_side1;
	side collision_side2;

	bool operator<(const collision& event) const
	{
		if (collider1.m_index < event.collider1.m_index)
		{
			return true;
		}
		if (collider1.m_index > event.collider1.m_index)
		{
			return false;
		}
		if (collider2.m_index < event.collider2.m_index)
		{
			return true;
		}
		if (collider2.m_index > event.collider2.m_index)
		{
			return false;
		}
		return false;
	}
};

struct static_dynamic_collision : public collision {};
struct static_triggerdynamic_collision : public collision {};
struct triggerstatic_dynamic_collision : public collision {};
struct kinematic_collision : public collision {};
struct dynamic_dynamic_collision : public collision {};

