#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include <vector>
#include <memory>

#include "AnimationComponent.h"
#include "SpriteComponent.h"
#include "Animation.h"
#include "Sprite.h"
#include "AnimationFrame.h"
#include "AssetStorage.h"
#include "Game.h"

struct AnimationComponent;
struct SpriteComponent;

class RenderingSystem
{
private:

	std::vector<std::shared_ptr<AnimationComponent>> animatedSprites;
	std::vector<std::shared_ptr<SpriteComponent>> staticSprites;

public:

	void add(std::shared_ptr<AnimationComponent>&& spA)
	{
		animatedSprites.emplace_back(std::move(spA)); //why move here?
	}

	void add(std::shared_ptr<SpriteComponent>&& spS)
	{
		staticSprites.emplace_back(std::move(spS)); //why move here?
	}
	
	void update()
	{
		if (Game::paused) return;
		for (auto& upAnimSpriteC : animatedSprites)
		{
			if (!upAnimSpriteC->isEnabled) continue;
			drawSprite(Game::assets->getAnimation(upAnimSpriteC->currentAnimation)->frames[upAnimSpriteC->currentFrame].spriteId);

		}
		for (auto& upSpriteC : staticSprites)
		{
			if (!upSpriteC->isEnabled) continue;
			drawSprite(upSpriteC->spriteId);
		}

	}

	inline void drawSprite(const SpriteId& id)
	{
		sf::Sprite& sprite = Game::assets->getSprite(id)->m_sprite;
		Game::window->draw(sprite);
	}

};