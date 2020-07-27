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
		auto transform = entity->get<TransformComponent>();
		auto playercomp = entity->get<PlayerComponent>();

		double eps = 1e-3;

		//FRICTION
		/*if (rigidbody->velocity.x > 0)
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
		}*/
		//if (upPressedDown) std::cout << "up pressed down" << std::endl;
		//MOVE MARIO
		if (ActionSystem::getActionValue(ActionName::Right))
		{
			rigidbody->velocity.x = playercomp->run_velocity;
			//rigidbody->velocity.x += playercomp->run_velocity/2;
			rigidbody->gravity = playercomp->fall_gravity;
		}
		if (ActionSystem::getActionValue(ActionName::Left))
		{
			rigidbody->velocity.x = -playercomp->run_velocity;
			//rigidbody->velocity.x -= playercomp->run_velocity/2;
			rigidbody->gravity = playercomp->fall_gravity;
		}
		if (ActionSystem::getActionValue(ActionName::Down))
		{
			rigidbody->velocity.y = -playercomp->jump_velocity;
			rigidbody->gravity = playercomp->jump_gravity; //?
		}

		static bool upPressedDown = false;
		static bool upPressedDown_prev = false;
		upPressedDown = !upPressedDown_prev && ActionSystem::getActionValue(ActionName::Up);

		upPressedDown_prev = ActionSystem::getActionValue(ActionName::Up);
		//if (ActionSystem::getActionValue(ActionName::Up))
		if(upPressedDown)
		{
			playercomp->curr_jumps++;
			if (playercomp->curr_jumps > playercomp->max_jumps)
			{
				playercomp->curr_jumps = playercomp->max_jumps;
			}
			else {
				//if (abs(rigidbody->velocity.y - playercomp->jump_velocity) < eps)
				if(playercomp->curr_jumps == 2)
				{
					rigidbody->velocity.y = playercomp->high_jump_velocity;
					rigidbody->gravity = playercomp->high_jump_gravity;
				}
				else if (playercomp->curr_jumps == 1) {
					rigidbody->velocity.y = playercomp->jump_velocity;
					rigidbody->gravity = playercomp->jump_gravity;
				}
			}
		}

		if (abs(rigidbody->velocity.x/rigidbody->friction) < eps)
		{
			//idle animation
		}

		if (playercomp->curr_jumps > 0)
		{
			rigidbody->friction = 1.1f;
			//jump animation
		}
		else if (playercomp->curr_jumps == 0)
		{
			rigidbody->friction = 1.5f;
		}

		bool flip_sprite = false;
		//which direction is sprite facing//flip sprite
		if ((static_cast<double>(transform->new_pos.x) - transform->pos.x) > eps)
		{
			if (rigidbody->direction == RigidBodyComponent::left)
			{
				flip_sprite = true;
			}
			rigidbody->direction = RigidBodyComponent::right;
		}
		else if ((static_cast<double>(transform->new_pos.x) - transform->pos.x) < -eps)
		{
			if (rigidbody->direction == RigidBodyComponent::right)
			{
				flip_sprite = true;
			}
			rigidbody->direction = RigidBodyComponent::left;
		}
		
		/*rigidbody->friction = 1.5f;
		if (playercomp->is_jumping)
		{
			rigidbody->friction = 1.0f;
		}
		else if (flip_sprite && !playercomp->is_jumping)
		{
			//play change direction animation
			//need to know change direction side too...
			rigidbody->friction = 9.0f;

		}*/
	}
}
