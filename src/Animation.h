#pragma once

#include <vector>
#include <string>

#include "json_serialization.h"

#include "AnimationFrame.h"

enum class animation_mode
{
	loop,
	one_time,
	ping_pong_forward,
	ping_pong_backward
};

struct Animation
{
	std::vector<AnimationFrame> frames;
	animation_mode mode;

};

void to_json(json& j, const Animation& p);
void from_json(const json& j, Animation& p);