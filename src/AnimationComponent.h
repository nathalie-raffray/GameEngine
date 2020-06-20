#pragma once

#include <SFML/System/Clock.hpp>

#include <string>

using AnimationId = std::string;
using AnimationCollectionId = std::string;
using Clock = sf::Clock;

struct AnimationComponent
{
	AnimationId currentAnimation;
	AnimationCollectionId animation_collection_id;

	int currentFrame = 0;
	Clock clock;
	
	bool isEnabled = true; //for animation editor / debugging

};


