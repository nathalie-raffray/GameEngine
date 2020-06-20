#include "PlayerComponent.h"
#include "PlayerController.h"
#include "ActionSystem.h"

bool PlayerController::isValid(EntityHandle h) const
{
	return (h->has<PlayerComponent>() && h->has<TransformComponent>());
}

void PlayerController::update(float dt)
{
	for (auto& entity : m_entities)
	{
		auto transform = entity->get<TransformComponent>();

		if (ActionSystem::getActionValue(Right))
		{
			transform->pos.x += 5;
		}
		if (ActionSystem::getActionValue(Left))
		{
			transform->pos.x -= 5;
		}
		if (ActionSystem::getActionValue(Up))
		{
			transform->pos.y -= 5;
		}
		if (ActionSystem::getActionValue(Down))
		{
			transform->pos.y += 5;
		}
	}
}
