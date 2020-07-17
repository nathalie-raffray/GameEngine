#include "PlayerComponent.h"
#include "PlayerController.h"
#include "ActionSystem.h"

bool PlayerController::isValid(EntityHandle h) const
{
	return (h->has<PlayerComponent>() && h->has<TransformComponent>() && h->has<RigidBodyComponent>());
}

void PlayerController::update(float dt)
{
	for (auto& entity : m_entities)
	{
		auto rigidbody = entity->get<RigidBodyComponent>();

		//FRICTION
		if (rigidbody->velocity.x > 0)
		{
			rigidbody->velocity.x = std::max<float>(rigidbody->velocity.x - 4, 0);
		}
		else {
			rigidbody->velocity.x = std::min<float>(rigidbody->velocity.x + 4, 0);
		}
		if (rigidbody->velocity.y > 0)
		{
			rigidbody->velocity.y = std::max<float>(rigidbody->velocity.y - 4, 0);
		}
		else {
			rigidbody->velocity.y = std::min<float>(rigidbody->velocity.y + 4, 0);
		}

		//MOVE MARIO
		if (ActionSystem::getActionValue(Right))
		{
			rigidbody->velocity.x += 5;
		}
		if (ActionSystem::getActionValue(Left))
		{
			rigidbody->velocity.x -= 5;
		}
		if (ActionSystem::getActionValue(Up))
		{
			rigidbody->velocity.y -= 5;
		}
		if (ActionSystem::getActionValue(Down))
		{
			rigidbody->velocity.y += 5;
		}
		
	}
}
