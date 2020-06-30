#pragma once
#include <unordered_map>
#include <string>
#include <memory>

#include "json_serialization.h"

#include "Animation.h"

using AnimationId = std::string;
using AssetId = std::string;

struct AnimationCollection : Asset
{
	std::unordered_map<AnimationId, std::unique_ptr<Animation>> animations;

	Animation* getAnimation(const AnimationId& id);

	static bool load(const std::string& filePath);

	~AnimationCollection() override = default;
};

void from_json(const json& j, AnimationCollection& ac);
void to_json(json& j, const AnimationCollection& ac);

