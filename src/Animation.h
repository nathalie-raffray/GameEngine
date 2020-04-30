#pragma once

#include <vector>
#include <string>

#include "json.hpp"

using nlohmann::json;

struct AnimationFrame;

struct Animation
{
	enum animation_mode
	{
		loop,
		one_time,
		ping_pong_forward, 
		ping_pong_backward
	};

	std::vector<AnimationFrame> frames;
	animation_mode mode;

};

void to_json(json& j, const Animation& p);
void from_json(const json& j, Animation& p);