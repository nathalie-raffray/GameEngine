#pragma once
//#include "EntityRegistry.h"
#include "Entity.h"

struct ColliderEvent
{
	EntityHandle collider1;
	EntityHandle collider2;

	bool operator<(const ColliderEvent& event) const;
};

struct StaticDynamicCollision //physics system handles these
{
	EntityHandle static_collider;
	EntityHandle dynamic_collider;
};

struct StaticTriggerDynamicCollision //eg. 
{
	EntityHandle static_collider;
	EntityHandle dynamic_collider;
};

struct KinematicCollision
{
	EntityHandle kinematic_collider;
	EntityHandle other_collider;
};

struct DynamicDynamicCollision
{
	EntityHandle dynamic_collider1;
	EntityHandle dynamic_collider2;
};