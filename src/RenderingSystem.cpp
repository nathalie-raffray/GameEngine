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

		Animation* animation = Game::assets->get<AnimationCollection>(upAnimSpriteC->animation_collection_id)->getAnimation(upAnimSpriteC->currentAnimation);
		
		if (!animation) continue;//for debug purposes

		int totalFrames = static_cast<int>(animation->frames.size());
		if (totalFrames == 0) continue; //for debug purposes

		Game::window->draw(animation->frames[upAnimSpriteC->currentFrame].sprite.m_sprite);
	}
	for (auto& upSpriteC : staticSprites)
	{
		if (!upSpriteC->isEnabled) continue;
		Sprite* s = Game::assets->get<Sprite>(upSpriteC->spriteId);
		if (s)
		{
			sf::Sprite& sprite = s->m_sprite;
			Game::window->draw(sprite);
		}
	}
}

//----------------------------------------------------------------------------------------------

void RenderingSystem::drawSprite(const SpriteId& id)
{
	Sprite* s = Game::assets->get<Sprite>(id);
	if (s)
	{
		sf::Sprite& sprite = s->m_sprite;
		Game::window->draw(sprite);
	}
}

//----------------------------------------------------------------------------------------------
