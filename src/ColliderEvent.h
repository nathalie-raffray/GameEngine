#pragma once
#include "EntityRegistry.h"

struct ColliderEvent
{
	EntityHandle collider1;
	EntityHandle collider2;

	bool operator<(const ColliderEvent& event) const;
};


