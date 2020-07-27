#pragma once

#include "Sprite.h"

//using SpriteId = std::string;

struct AnimationFrame
{
	//SpriteId spriteId;
	Sprite sprite;

	int screenOffsetX=0;
	int screenOffsetY=0;

	float duration;

};
