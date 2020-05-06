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

//----------------------------------------------------------------------------------------------

void RenderingSystem::add(const std::shared_ptr<AnimationComponent>& spA)
{
	animatedSprites.emplace_back(spA);
}

//----------------------------------------------------------------------------------------------

void RenderingSystem::update()
{
	//if (Game::paused) return;
	for (auto& upAnimSpriteC : animatedSprites)
	{
		if (!upAnimSpriteC->isEnabled) continue;

		Animation* animation = Game::assets->getAnimationCollection(upAnimSpriteC->animation_collection_id)->getAnimation(upAnimSpriteC->currentAnimation);

		int totalFrames = static_cast<int>(animation->frames.size());
		if (totalFrames == 0) continue; //for debug purposes

		drawSprite(animation->frames[upAnimSpriteC->currentFrame].spriteId);

	}
	for (auto& upSpriteC : staticSprites)
	{
		if (!upSpriteC->isEnabled) continue;
		drawSprite(upSpriteC->spriteId);
	}
}

//----------------------------------------------------------------------------------------------

void RenderingSystem::drawSprite(const SpriteId& id)
{
	Sprite* s = Game::assets->getSprite(id);
	if (s)
	{
		sf::Sprite& sprite = s->m_sprite;
		Game::window->draw(sprite);
	}
}

//----------------------------------------------------------------------------------------------
