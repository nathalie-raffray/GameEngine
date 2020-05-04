#pragma once

#include <SFML/System/Clock.hpp>

#include <string>

using AnimationId = std::string;
//using AnimationCollectionId = std::string;
using Clock = sf::Clock;

struct AnimationComponent
{
	AnimationId currentAnimation;
	//AnimationCollectionId animation_collection_Id;

	int currentFrame = 0;
	Clock clock;
	bool isEnabled; //for animation editor / debugging
	//int id; //this could be used?

	AnimationComponent(AnimationId ca) : currentAnimation(ca) {}
};