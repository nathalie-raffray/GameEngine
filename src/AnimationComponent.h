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

	//if debug 
	static inline const char* name = "animation component"; 
};

/***************** JSON SERIALIZATION **********************/
#include "json_serialization.h"

inline void to_json(json& j, const AnimationComponent& p)
{
	TRY_PARSE(j["currentAnimation"] = p.currentAnimation);
	TRY_PARSE(j["animation_collection_id"] = p.animation_collection_id);
}
inline void from_json(const json& j, AnimationComponent& p)
{
	TRY_PARSE(p.currentAnimation = j.at("currentAnimation"));
	TRY_PARSE(p.animation_collection_id = j.at("animation_collection_id"));
	p.currentFrame = 0;
}

