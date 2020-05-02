#pragma once

#include <string>

using SpriteId = std::string;

struct AnimationFrame
{
	SpriteId spriteId;

	int screenOffsetX;
	int screenOffsetY;

	float duration;

	AnimationFrame(const SpriteId& id, int sx, int sy, float d)
		: spriteId(id), screenOffsetX(sx), screenOffsetY(sy), duration(d) {}

	AnimationFrame()
		: spriteId(""), screenOffsetX(0), screenOffsetY(0), duration(0) {}

	AnimationFrame(const SpriteId& id)
		: spriteId(id), screenOffsetX(0), screenOffsetY(0), duration(0) {}

};
