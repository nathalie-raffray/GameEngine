#pragma once
#include <string>

using SpriteId = std::string;

struct SpriteComponent
{
	// Serializable attribute
	SpriteId spriteId;
	// Transient attributes
	bool isEnabled;

	static inline const char* name = "sprite component";
};

/***************** JSON SERIALIZATION **********************/
#include "json_serialization.h"

inline void to_json(json& j, const SpriteComponent& p)
{
	TRY_PARSE(j["spriteId"] = p.spriteId);
}
inline void from_json(const json& j, SpriteComponent& p)
{
	TRY_PARSE(p.spriteId = j.at("spriteId"));
}