#pragma once
struct PlayerComponent
{
	float speed;
};

/***************** JSON SERIALIZATION **********************/
#include "json_serialization.h"

inline void to_json(json& j, const PlayerComponent& p)
{
	j["speed"] = p.speed;
}
inline void from_json(const json& j, PlayerComponent& p)
{
	TRY_PARSE(p.speed = j.at("speed").get<float>());
}