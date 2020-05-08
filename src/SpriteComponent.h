#pragma once
#include <string>

using SpriteId = std::string;

struct SpriteComponent
{
	// Serializable attribute
	SpriteId spriteId;
	// Transient attributes
	bool isEnabled;
};

