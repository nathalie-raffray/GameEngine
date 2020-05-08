#include "RenderingSystem.h"

#include <SFML/Graphics/Sprite.hpp>

#include "AnimationComponent.h"
#include "SpriteComponent.h"
#include "Animation.h"
#include "Sprite.h"
#include "AnimationFrame.h"
#include "AssetStorage.h"
#include "Game.h"
#include "AnimationCollection.h"
#include "Entity.h"

//----------------------------------------------------------------------------------------------

bool RenderingSystem::isValid(const EntityHandle& h)
{
	if (h->has<AnimationComponent>() || h->has<SpriteComponent>()) return true;
	return false;
}

//----------------------------------------------------------------------------------------------

void RenderingSystem::update(float dt)
{
	dt = 0; //temporary: so that compiler doesnt give warning. 
	for (auto& entity : m_entities)
	{
		//if (!upAnimSpriteC->isEnabled) continue;
		if (entity->has<AnimationComponent>())
		{
			auto animation_component = entity->get<AnimationComponent>();
			Animation* animation = Game::assets->get<AnimationCollection>(animation_component->animation_collection_id)->getAnimation(animation_component->currentAnimation);

			if (!animation) continue;//for debug purposes

			int totalFrames = static_cast<int>(animation->frames.size());
			if (totalFrames == 0) continue; //for debug purposes

			Game::window->draw(animation->frames[animation_component->currentFrame].sprite.m_sprite);
		}
		if (entity->has<SpriteComponent>())
		{
			//if (!upSpriteC->isEnabled) continue;
			auto sprite_component = entity->get<SpriteComponent>();
			Sprite* s = Game::assets->get<Sprite>(sprite_component->spriteId);
			if (s)
			{
				sf::Sprite& sprite = s->m_sprite;
				Game::window->draw(sprite);
			}

		}
	}
}
