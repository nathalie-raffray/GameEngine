#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

#include "AnimationComponent.h"
#include "Animation.h"
#include "AnimationFrame.h"
#include "AssetStorage.h"
#include "Sprite.h"
#include "Game.h"
#include "AnimationCollection.h"

extern AssetStorage assets;

class AnimationSystem
{
private:
	std::vector<std::shared_ptr<AnimationComponent>> animatedSprites;

public:
	
	/*void add(std::shared_ptr<AnimationComponent>&& spA)
	{
		animatedSprites.emplace_back(spA); // move here?
		//im guessing shared_ptr has a move constructor that takes a rvalue
	}*/

	void add(const std::shared_ptr<AnimationComponent>& spA)
	{
		animatedSprites.emplace_back(spA); //pretty sure this will make a copie
	}

	void play(const AnimationId& newAnimation, std::shared_ptr<AnimationComponent>& spA)
	{
		spA->currentAnimation = newAnimation;
		spA->clock.restart();
	}

	void update()
	{
		if (Game::paused) return;
		
		for (auto& animSprite : animatedSprites)
		{
			//if (!animSprite->isEnabled) continue;
			Animation* animation = Game::assets->getAnimationCollection(animSprite->animation_collection_id)->getAnimation(animSprite->currentAnimation);
				//getAnimation(animSprite->currentAnimation);
			//assert(animation);
			int currFrame = animSprite->currentFrame;
			int totalFrames = static_cast<int>(animation->frames.size());

			//std::cout << totalFrames;
			if (totalFrames == 0) return; //for debug purposes
			
			AnimationFrame& frame = animation->frames[currFrame];

			if (frame.duration <= animSprite->clock.getElapsedTime().asMilliseconds())
			{
				animSprite->clock.restart();
				switch (animation->mode)
				{
				case Animation::loop:
					animSprite->currentFrame = (currFrame + 1) % totalFrames;
					break;

				case Animation::one_time:
					animSprite->currentFrame = std::min(currFrame + 1, totalFrames - 1);
					break;

				case Animation::ping_pong_forward:
					if (currFrame == totalFrames - 1)
					{
						animation->mode = Animation::ping_pong_backward;
						animSprite->currentFrame = (currFrame - 1) % totalFrames;
					}
					else animSprite->currentFrame = (currFrame + 1) % totalFrames;
					break;

				case Animation::ping_pong_backward:
					if (currFrame == 0)
					{
						animation->mode = Animation::ping_pong_forward;
						animSprite->currentFrame = (currFrame + 1) % totalFrames;
					}
					else animSprite->currentFrame = (currFrame - 1) % totalFrames;
					break;
				}		
			}

		}
	}
};

/*
struct AnimationSystem
{
	std::vector<SpriteComponent> sprites;

	void play(SpriteComponent s, string animationName)
	{
		s.timeAccumulator = 0.0;
	}

	void update(float dt)
	{
		for (auto spriteComp : sprites)
		{
			Sprite sprite = AssetStorage::get(spriteComp.spriteId);

			Animation currentAnim = sprite.animations[spriteComp.currentAnimation];

			auto currentFrame = currentAnim.frames[spriteComp.currentFrame];
			spriteComp.timeAccumulator += dt;

			if (spriteComp.timeAccumulator > currentFrame.timestamp)
			{
				if (currentAnim.loop)
				{
					spriteComp.currentFrame = (spriteComp.currentFrame + 1) % currentAnim.frames.size();
				}
				else
				{
					spriteComp.currentFrame = std::min(spriteComp.currentFrame + 1, currentAnim.frames.size() - 1);
				}
			}
		}
	}
};
*/

/*
#pragma once
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <iostream>
#include <unordered_map>

#include "ResourceManager.h"
#include "SpriteComponent.h"

typedef sf::IntRect IntRect;
typedef sf::Clock Clock;
typedef sf::Sprite Sprite;
template <typename T>
using Vector2 = sf::Vector2<T>; //Vector<2> is equivalent to sf::Vector2<T>

typedef sf::Texture Texture;

class AnimationSystem
{
private:
	//list of entities eventually
	CAnimatedSprite* spriteComponent;
	std::vector<std::unique_ptr<CAnimatedSprite>> sprites;
	
	Clock clock; //int64
public:
	friend class ImguiWindows;

	AnimationSystem(CAnimatedSprite* sc) : spriteComponent(sc) {}
	AnimationSystem() {}
	~AnimationSystem();

	//the unique pointer tells animation system that it takes ownership
	//since its a //unique// pointer
	void add(std::unique_ptr<CAnimatedSprite> sprite);
	void remove(CAnimatedSprite* sc);

	void playAnimation(std::string name);
	void pauseAnimation();

	void update();
	void draw(sf::RenderWindow& window) { for (CAnimatedSprite* sprite : sprites) if(sprite->isEnabled()) window.draw(sprite->m_sprite);  }

	inline void updateTextureRect(CAnimatedSprite* sc);
	inline void updatePositionOffset(CAnimatedSprite* sc);
	inline void updateScale(CAnimatedSprite* sc);
	inline void updateRotation(CAnimatedSprite* sc, float angle);

	void imguiAnimationEditor();

};

*/