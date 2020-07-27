#pragma once
#include "SideEnum.h"

using AnimationId = std::string;

struct AIComponent
{
	side vulnerable_to_player;
	
	//animationId hit_animation
	//can use this for blocks as well 
	//bool vulnerable_to_shell;
};

/***************** JSON SERIALIZATION **********************/
#include "json_serialization.h"

inline void to_json(json& j, const AIComponent& p)
{
	if (p.vulnerable_to_player != side::none) j["vulnerable_to_player"] = GetString(p.vulnerable_to_player);
}
inline void from_json(const json& j, AIComponent& p)
{
	TRY_PARSE_ELSE(p.vulnerable_to_player = GetsideValue(j.at("vulnerable_to_player").get<std::string>().c_str()), p.vulnerable_to_player = side::none);
}
