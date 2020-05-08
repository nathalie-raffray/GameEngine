#pragma once
#//include <string>

#include "Sprite.h"

//using SpriteId = std::string;

struct AnimationFrame
{
	//SpriteId spriteId;
	Sprite sprite;

	int screenOffsetX=0;
	int screenOffsetY=0;

	float duration;

	//~AnimationFrame() = default;

	//TAKE THESE OUT, TRY TO MAKE THEM POD, PLAIN OLD DATA
	//IF PLAIN OLD DATA STRUCTURE, THEN IT DOESNT CALL CONSTRUCTOR
	//ON INITIALIZATION BUT MEMCPY
	/*
	AnimationFrame(const SpriteId& id, int sx, int sy, float d)
		: spriteId(id), screenOffsetX(sx), screenOffsetY(sy), duration(d) {}

	AnimationFrame()
		: spriteId(""), screenOffsetX(0), screenOffsetY(0), duration(0) {}

	AnimationFrame(const SpriteId& id)
		: spriteId(id), screenOffsetX(0), screenOffsetY(0), duration(0) {}
	*/

};
