#include "RigidbodyPhysics.h"
#include "AssetStorage.h"
#include "AnimationCollection.h"


//----------------------------------------------------------------------------------------------

bool RigidbodyPhysics::isValid(EntityHandle eh) const
{
	return eh->has<RigidBodyComponent>() && eh->has<TransformComponent>();
}

//----------------------------------------------------------------------------------------------

void RigidbodyPhysics::init(EntityHandle eh)
{

}

//----------------------------------------------------------------------------------------------

void RigidbodyPhysics::update(float dt)
{
	for (auto entity : m_entities)
	{
		auto transform = entity->get<TransformComponent>();
		auto rigidbody = entity->get<RigidBodyComponent>();

		if (!rigidbody->is_kinematic)
		{
			//then apply gravity
			//rigidbody->velocity.y += 1;
		}

		transform->new_pos = transform->pos + static_cast<Vector2<int>>(rigidbody->velocity);

		double eps = 1e-3;

		bool flip_sprite = false;
		//which direction is sprite facing//flip sprite
		if ((transform->new_pos.x - transform->pos.x) > eps)
		{
			if (rigidbody->direction == RigidBodyComponent::left)
			{       
				flip_sprite = true;
			}
			rigidbody->direction = RigidBodyComponent::right;
		}
		else if ((transform->new_pos.x - transform->pos.x) < -eps)
		{
			if (rigidbody->direction == RigidBodyComponent::right)
			{
				flip_sprite = true;
			}
			rigidbody->direction = RigidBodyComponent::left;
		}

		//FLIPPING SPRITE
		if (flip_sprite)
		{
			if (entity->has<AnimationComponent>())
			{
				auto animComp = entity->get<AnimationComponent>();
				Animation* animation = Game::assets->get<AnimationCollection>(animComp->animation_collection_id)->getAnimation(animComp->currentAnimation);
				for (auto& frame : animation->frames)
				{
					frame.sprite.texRect.left += frame.sprite.texRect.width;
					frame.sprite.texRect.width *= -1;
				}
			}
			else if (entity->has<SpriteComponent>())
			{
				auto& texRect = Game::assets->get<Sprite>(entity->get<SpriteComponent>()->spriteId)->texRect;
				texRect.left += texRect.width;
				texRect.width *= -1;

			}
		}


	}
}

//----------------------------------------------------------------------------------------------

void RigidbodyPhysics::handle(const static_dynamic_collision& event)
{
	auto static_transform = event.collider1->get<TransformComponent>();
	auto dynamic_transform = event.collider2->get<TransformComponent>();

	auto rigidbody = event.collider2->get<RigidBodyComponent>();

	auto static_bounds = static_cast<sf::IntRect>(Sprite::getBounds(event.collider1));
	auto dynamic_bounds = static_cast<sf::IntRect>(Sprite::getBounds(event.collider2));

	auto& new_pos = dynamic_transform->new_pos;

	switch (event.collision_side2)
	{
	case collision::side::left:
		new_pos.x = static_transform->pos.x + static_bounds.width;
		if (rigidbody->velocity.x < 0) rigidbody->velocity.x = 0;
		break;

	case collision::side::right:
		new_pos.x = static_transform->pos.x - dynamic_bounds.width;
		if (rigidbody->velocity.x > 0) rigidbody->velocity.x = 0;
		break;

	case collision::side::top:
		new_pos.y = static_transform->pos.y + static_bounds.height;
		if (rigidbody->velocity.y < 0) rigidbody->velocity.y = 0;
		break;

	case collision::side::bottom:
		new_pos.y = static_transform->pos.y - dynamic_bounds.height;
		if (rigidbody->velocity.y > 0) rigidbody->velocity.y = 0;
		break;
	}

	//this is for corner case. 
	switch (event.collision_side1)
	{
	case collision::side::left:

		if (event.collision_side2 == collision::side::right) break;
		new_pos.x = static_transform->pos.x - dynamic_bounds.width;
		if (rigidbody->velocity.x > 0) rigidbody->velocity.x = 0;
		break;

	case collision::side::right:

		if (event.collision_side2 == collision::side::left) break;
		new_pos.x = static_transform->pos.x + static_bounds.width;
		if (rigidbody->velocity.x < 0) rigidbody->velocity.x = 0;
		break;

	case collision::side::top:

		if (event.collision_side2 == collision::side::bottom) break;
		new_pos.y = static_transform->pos.y - dynamic_bounds.height;
		if (rigidbody->velocity.y > 0) rigidbody->velocity.y = 0;
		break;

	case collision::side::bottom:

		if (event.collision_side2 == collision::side::top) break;
		new_pos.y = static_transform->pos.y + static_bounds.height;
		if (rigidbody->velocity.y < 0) rigidbody->velocity.y = 0;
		break;
	}

}

//----------------------------------------------------------------------------------------------
