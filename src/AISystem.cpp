#include "AISystem.h"

bool AISystem::isValid(EntityHandle h) const
{
	return h->has<HealthComponent>();
}

void AISystem::update(float dt)
{
	//for (auto& entity : m_entities)
	//{
		//auto health = entity->get<HealthComponent>();

		//if(health->curr_health != 0)
	//}
}

void AISystem::handle(const dynamic_dynamic_collision& event)
{
}

void AISystem::handle(const triggerstatic_dynamic_collision& event)
{
	if (event.collider2->has<PlayerComponent>() && event.collider2->has<HitboxComponent>())
	{
		auto player_hitbox = event.collider2->get<HitboxComponent>();
		auto player_animation = event.collider2->get<AnimationComponent>();
		
		if (event.collider1->has<HealthComponent>())
		{
			auto enemy_health = event.collider1->get<HealthComponent>();
			auto enemy_animation = event.collider1->get<AnimationComponent>();

			if (event.collider1->has<HitboxComponent>())
			{
				auto enemy_hitbox = event.collider1->get<HitboxComponent>();
				if (event.collider2->has<HealthComponent>()) //if player doesnt have health component, it just inflicts damage
				{
					auto player_health = event.collider2->get<HealthComponent>();
					if (event.collision_side1 != enemy_hitbox->vulnerable_to_player)
					{
						if (enemy_hitbox->damage_to_other > 0)
						{
							player_health->curr_health -= enemy_hitbox->damage_to_other;
							//player state needs to change to hit state
							//decrease to little mario
						}
						return;
					}
				}
				
				if (!enemy_hitbox->takes_partial_damage && enemy_health->curr_health - player_hitbox->damage_to_other > 0)
				{
					/*if (enemy_health->hit_animation != "INVALID")
					{
						//change animation or eventually change to hit state
						enemy_animation->currentAnimation = enemy_health->hit_animation;
						enemy_animation->currentFrame = 0;
						enemy_animation->clock.restart();
						return;
					}*/
				}
				enemy_health->curr_health -= player_hitbox->damage_to_other;
			}
		}
	}
	//else if the dynamic collider is a shell
}
