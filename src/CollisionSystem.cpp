#include "CollisionSystem.h"
#include "ColliderComponent.h"

bool CollisionSystem::isValid(EntityHandle) const
{
	//if (eh->has<ColliderComponent>()) return true;
	return false;
}

void CollisionSystem::update(float)
{
	//certain layers collide with other layers
	//
}
