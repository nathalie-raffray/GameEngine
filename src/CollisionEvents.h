#pragma once

#include "Entity.h"

struct collision
{
	enum class side
	{
		left, right, bottom, top
	};
	
	EntityHandle collider1;
	EntityHandle collider2;

	side collision_side1;
	side collision_side2;

	//collision(EntityHandle c1, EntityHandle c2, const collision& base) :
		//collider1(c1), collider2(c2), collision_side1(base.collision_side1), collision_side2(base.collision_side2), pen_X(base.pen_X), pen_Y(base.pen_Y) {}

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

