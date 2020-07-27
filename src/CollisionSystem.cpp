#include "CollisionSystem.h"

#include "AnimationCollection.h"
#include "AssetStorage.h"

//----------------------------------------------------------------------------------------------

bool CollisionSystem::isValid(EntityHandle eh) const
{
	return eh->has<ColliderComponent>() && eh->has<TransformComponent>() && (eh->has<AnimationComponent>() || eh->has<SpriteComponent>());
}

//----------------------------------------------------------------------------------------------

void CollisionSystem::update(float dt)
{
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it)
	{
		for (auto it2 = it+1; it2 != m_entities.end(); ++it2)
		{
			EntityHandle entity1 = *it;
			EntityHandle entity2 = *it2;
			    
			collision base_event;
			if (AABBCollision(entity1, entity2, base_event))
			{
				auto collider1 = entity1->get<ColliderComponent>();
				auto collider2 = entity2->get<ColliderComponent>();

				if (entity1->has<RigidBodyComponent>() || entity2->has<RigidBodyComponent>())
				{
					if (entity1->has<RigidBodyComponent>() && entity2->has<RigidBodyComponent>())
					{
						if (!(entity1->get<RigidBodyComponent>()->is_kinematic && entity2->get<RigidBodyComponent>()->is_kinematic))
						{
							dynamic_dynamic_collision event = { entity1, entity2, base_event.collision_side1, base_event.collision_side2};
							EventManager::events<dynamic_dynamic_collision>.insert(event);
						}
					}
					else
					{
						if (entity1->has<RigidBodyComponent>())
						{
							if (collider1->is_trigger || collider2->is_trigger)
							{
								if (collider2->is_trigger)
								{
									triggerstatic_dynamic_collision event = { entity2, entity1, base_event.collision_side2, base_event.collision_side1};
									EventManager::events<triggerstatic_dynamic_collision>.insert(event);
								}
								if (collider1->is_trigger)
								{
									static_triggerdynamic_collision event = { entity2, entity1, base_event.collision_side2, base_event.collision_side1};
									EventManager::events<static_triggerdynamic_collision>.insert(event);
								}
							}
							else if (!entity1->get<RigidBodyComponent>()->is_kinematic)
							{
								static_dynamic_collision event = { entity2, entity1, base_event.collision_side2, base_event.collision_side1};
								EventManager::events<static_dynamic_collision>.insert(event);
							}
						}
						else if (entity2->has<RigidBodyComponent>())
						{
							if (collider1->is_trigger || collider2->is_trigger)
							{
								if (collider1->is_trigger)
								{
									triggerstatic_dynamic_collision event = { entity1, entity2, base_event.collision_side1, base_event.collision_side2 };
									EventManager::events<triggerstatic_dynamic_collision>.insert(event);
								}
								if (collider2->is_trigger)
								{
									static_triggerdynamic_collision event = { entity1, entity2, base_event.collision_side1, base_event.collision_side2 };
									EventManager::events<static_triggerdynamic_collision>.insert(event);
								}
							}
							else if (!entity2->get<RigidBodyComponent>()->is_kinematic)
							{
								static_dynamic_collision event = { entity1, entity2, base_event.collision_side1, base_event.collision_side2 };
								EventManager::events<static_dynamic_collision>.insert(event);
							}
						}
					}
				}
			}
		}
	}
}

//----------------------------------------------------------------------------------------------

bool CollisionSystem::AABBCollision(EntityHandle e1, EntityHandle e2, collision& base_event)
{
	double eps = 1e-3;
	
	auto screenRect1 = Sprite::getBounds(e1);
	auto screenRect2 = Sprite::getBounds(e2);
	
	auto& pos1 = e1->get<TransformComponent>()->new_pos;
	auto& pos2 = e2->get<TransformComponent>()->new_pos;

	auto& prevpos1 = e1->get<TransformComponent>()->pos;
	auto& prevpos2 = e2->get<TransformComponent>()->pos;

	//collision within bounds of rects.
	bool collisionX = (pos1.x <= pos2.x && pos1.x + screenRect1.width >= pos2.x) || (pos2.x <= pos1.x && pos2.x + screenRect2.width >= pos1.x);
	bool collisionY = (pos1.y <= pos2.y && pos1.y + screenRect1.height >= pos2.y) || (pos2.y <= pos1.y && pos2.y + screenRect2.height >= pos1.y);

	bool collisionX_BetweenFrames = (prevpos1.x <= prevpos2.x && pos1.x + screenRect1.width >= pos2.x) || (prevpos2.x <= prevpos1.x && pos2.x + screenRect2.width >= pos1.x);
	bool collisionY_BetweenFrames = (prevpos1.y <= prevpos2.y && pos1.y + screenRect1.height >= pos2.y) || (prevpos2.y <= prevpos1.y && pos2.y + screenRect2.height >= pos1.y);

	if (!(collisionX && collisionY) && !(collisionX_BetweenFrames && collisionY_BetweenFrames)) return false;

	//if (collisionX_BetweenFrames && collisionY_BetweenFrames) std::cout << "collision between frames detected" << std::endl;
	//if (!(collisionX && collisionY)) std::cout << "collision between frames detected" << std::endl;

	bool bias_X = pos1.x < pos2.x;
	bool bias_Y = pos1.y < pos2.y;

	// calculate penetration depths in each direction
	float pen_X = (bias_X ? (pos1.x + screenRect1.width - pos2.x)
		: (pos2.x + screenRect2.width - pos1.x));
	float pen_Y = (bias_Y ? (pos1.y + screenRect1.height - pos2.y)
		: (pos2.y + screenRect2.height - pos1.y));
	float diff = pen_X - pen_Y;

	bool bias_prevX = prevpos1.x < prevpos2.x;
	bool bias_prevY = prevpos1.y < prevpos2.y;

	// X penetration greater
	if (diff > eps)
	{
		//resolve vertical collision
		//base_event.collision_side1 = ((bias_Y && collisionY) || (bias_prevY && !collisionY) ? side::bottom : side::top);
		base_event.collision_side1 = (bias_prevY ? side::bottom : side::top);
		base_event.collision_side2 = (bias_prevY ? side::top : side::bottom);
	}

	// Y pentration greater
	else if (diff < -eps)
	{
		//resolve horizontal collision
		base_event.collision_side1 = (bias_prevX ? side::right : side::left);
		base_event.collision_side2 = (bias_prevX ? side::left : side::right);
	}

	// both penetrations are approximately equal -> treat as corner collision
	else 
	{
		base_event.collision_side1 = (bias_prevX ? side::right : side::left);
		base_event.collision_side2 = (bias_prevY ? side::top : side::bottom);
	}

	return true;
}

//----------------------------------------------------------------------------------------------
