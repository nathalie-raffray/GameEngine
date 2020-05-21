#include "CollisionSystem.h"
#include "ColliderComponent.h"
#include "AnimationComponent.h"
#include "AnimationCollection.h"
#include "Animation.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "AssetStorage.h"
#include "EventManager.h"

bool CollisionSystem::isValid(EntityHandle eh) const
{
	//return eh->has<ColliderComponent>() && eh->has<AnimationComponent>();
	return eh->has<ColliderComponent>();

}

void CollisionSystem::update(float)
{
	for (auto it = m_entities.begin(); it < m_entities.end(); it++ )
	{
		for (auto it2 = it+1; it2 < m_entities.end(); it2++)
		{
			//if (AABBCollision(*it, *it2))
			//{
				ColliderEvent event;
				event.collider1 = *it;
				event.collider2 = *it2;

				EventManager::events<ColliderEvent>.insert(event);
			//}
		}
	}
}

bool CollisionSystem::AABBCollision(EntityHandle e1, EntityHandle e2)
{
	//holy crap need to make transform component
	
	auto c1 = e1->get<AnimationComponent>();
	Animation* animation1 = Game::assets->get<AnimationCollection>(c1->animation_collection_id)->getAnimation(c1->currentAnimation);
	auto sprite1 = animation1->frames[c1->currentFrame].sprite.m_sprite;

	auto screenRect1 = sprite1.getGlobalBounds();
	auto pos1 = screenRect1.getPosition();

	auto c2 = e1->get<AnimationComponent>();
	Animation* animation2 = Game::assets->get<AnimationCollection>(c2->animation_collection_id)->getAnimation(c2->currentAnimation);
	auto sprite2 = animation2->frames[c2->currentFrame].sprite.m_sprite;

	auto screenRect2 = sprite2.getGlobalBounds();
	auto pos2 = screenRect2.getPosition();

	if ( (pos1.x <= pos2.x && pos1.x + screenRect1.width >= pos2.x)
					|| (pos2.x <= pos1.x && pos2.x + screenRect2.width >= pos1.x))
	{
		if ((pos1.y <= pos2.y && pos1.y + screenRect1.height >= pos2.y)
					|| (pos2.y <= pos1.y && pos2.y + screenRect2.height >= pos1.y))
		{
			return true;
		}
	}

	return false;
}
