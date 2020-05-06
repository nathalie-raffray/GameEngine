#pragma once
#include <unordered_map>
#include <string>
#include <memory>

#include "json.hpp"

using nlohmann::json;

using AnimationId = std::string;

struct Animation;

struct AnimationCollection
{
	std::unordered_map<AnimationId, std::unique_ptr<Animation>> animations;

	Animation* getAnimation(const AnimationId& id);
};

void from_json(const json& j, AnimationCollection ac);
void to_json(json& j, const AnimationCollection ac);

