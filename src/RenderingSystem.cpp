#include "RenderingSystem.h"

#include <SFML/Graphics/Sprite.hpp>

#include "AnimationComponent.h"
#include "SpriteComponent.h"
#include "Animation.h"
#include "Sprite.h"
#include "AnimationFrame.h"
#include "AssetStorage.h"
#include "Game.h"

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

		int totalFrames = static_cast<int>(Game::assets->getAnimation(upAnimSpriteC->currentAnimation)->frames.size());
		if (totalFrames == 0) continue; //for debug purposes

		drawSprite(Game::assets->getAnimation(upAnimSpriteC->currentAnimation)->frames[upAnimSpriteC->currentFrame].spriteId);

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
