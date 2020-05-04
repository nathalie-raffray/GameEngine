#pragma once
#include <string>

using SpriteId = std::string;

struct SpriteComponent
{
	// Serializable attribute
	SpriteId spriteId;
	bool isEnabled;
	// Transient attributes
};

