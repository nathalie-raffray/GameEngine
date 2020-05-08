#include <algorithm>
#include <iostream>

#include "AnimationSystem.h"
#include "AnimationComponent.h"
#include "Animation.h"
#include "AnimationFrame.h"
#include "AssetStorage.h"
#include "Sprite.h"
#include "Game.h"
#include "AnimationCollection.h"

//----------------------------------------------------------------------------------------------

void AnimationSystem::add(const std::shared_ptr<AnimationComponent>& spA)
{
	animatedSprites.emplace_back(spA);
}

//----------------------------------------------------------------------------------------------

void AnimationSystem::play(const AnimationId& newAnimation, std::shared_ptr<AnimationComponent>& spA)
{
	spA->currentAnimation = newAnimation;
	spA->clock.restart();
}

//----------------------------------------------------------------------------------------------

void AnimationSystem::update()
{
	if (Game::paused) return;

	for (auto& animSprite : animatedSprites)
	{
		//if (!animSprite->isEnabled) continue;
		Animation* animation = Game::assets->get<AnimationCollection>(animSprite->animation_collection_id)->getAnimation(animSprite->currentAnimation);
		
		if (!animation) continue; //for debug purposes

		int currFrame = animSprite->currentFrame;
		int totalFrames = static_cast<int>(animation->frames.size());

		if (totalFrames == 0) return; //for debug purposes

		AnimationFrame& frame = animation->frames[currFrame];

		if (frame.duration <= animSprite->clock.getElapsedTime().asMilliseconds())
		{
			animSprite->clock.restart();
			switch (animation->mode)
			{
			case animation_mode::loop:
				animSprite->currentFrame = (currFrame + 1) % totalFrames;
				break;

			case animation_mode::one_time:
				animSprite->currentFrame = std::min(currFrame + 1, totalFrames - 1);
				break;

			case animation_mode::ping_pong_forward:
				if (currFrame == totalFrames - 1)
				{
					animation->mode = animation_mode::ping_pong_backward;
					animSprite->currentFrame = (currFrame - 1) % totalFrames;
				}
				else animSprite->currentFrame = (currFrame + 1) % totalFrames;
				break;

			case animation_mode::ping_pong_backward:
				if (currFrame == 0)
				{
					animation->mode = animation_mode::ping_pong_forward;
					animSprite->currentFrame = (currFrame + 1) % totalFrames;
				}
				else animSprite->currentFrame = (currFrame - 1) % totalFrames;
				break;
			}
		}

	}
}

//----------------------------------------------------------------------------------------------



/*
#define COMP(Name) if (j["name"] == #Name##Component) { auto c = new NameComponent; *c = j; a = c; }

void from_json(const json &js, Entity &e)
{
	for (auto j : js["components"])
	{
		Component *a = nullptr;
		COMP(Transform);
		COMP(Sprite);
		COMP(...)
		if (a)
		{
			e.comps.emplace_back(a);
		}

	}
}

void serialize()
{
	std::vector<Transform> trans;
	std::ifstream i(filePath);

	json j;
	i >> j;

	trans = j;
}
*/

