#pragma once

#include <vector>
#include <string>

#include "json_serialization.h"

#include "AnimationFrame.h"

using AnimationId = std::string;

enum class animation_mode
{
	loop,
	one_time,
	ping_pong_forward,
	ping_pong_backward,
	flash //for when mario gets hit
};

struct Animation
{
	std::vector<AnimationFrame> frames;
	animation_mode mode;

	static void set(EntityHandle h, AnimationId new_animation);
};

void to_json(json& j, const Animation& p);
void from_json(const json& j, Animation& p);