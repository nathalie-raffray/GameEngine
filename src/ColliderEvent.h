#pragma once
//#include "EntityRegistry.h"
#include "Entity.h"

struct ColliderEvent
{
	EntityHandle collider1;
	EntityHandle collider2;

	bool operator<(const ColliderEvent& event) const;
};


