#pragma once
#include <unordered_map>
#include <string>
#include <memory>

using AnimationId = std::string;

struct Animation;

struct AnimationCollection
{
	std::unordered_map<AnimationId, std::unique_ptr<Animation>> animations;
};