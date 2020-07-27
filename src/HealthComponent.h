#pragma once
//#include "SideEnum.h"

using AnimationId = std::string;
//using INVALID = "INVALID";

struct HealthComponent
{
	int max_health;
	int curr_health;

	//maybe you could put those two in animation component, or need a state->animation (fsm)

	//bool despawns_after_death; //for question mark blocks. maybe if death_animation is INVALID, it just doesn't despawn. 

	//put this in a component? for blocks that little mario can't hit (only mushroom mario can, so time_till_rejuvenate would be 0) and koopas. 
	//bool can_rejuvenate;
	//AnimationId rejuvenation_animation;
	//float time_till_rejuvenate;
	//idk. i guess for shells i can just have a shellcontroller script. 

	//bool vulnerable_to_shell;
	//or i could have that certain prefabs can collide with other prefabs
	//or like in unity, certain layers collide with other layers. 
	static inline const char* name = "health component";

};

/***************** JSON SERIALIZATION **********************/
#include "json_serialization.h"

inline void to_json(json& j, const HealthComponent& p)
{
	j["max_health"] = p.max_health;
	//if(p.death_animation != "INVALID") j["death_animation"] = p.death_animation;
	//if (p.hit_animation != "INVALID") j["hit_animation"] = p.hit_animation;
	//if (p.vulnerable_to_mario != side::none) j["vulnerable_to_mario"] = GetString(p.vulnerable_to_mario);
}
inline void from_json(const json& j, HealthComponent& p)
{
	TRY_PARSE_ELSE(p.max_health = j.at("max_health"), p.max_health = 1);
	p.curr_health = p.max_health;
	//TRY_PARSE_ELSE(p.death_animation = j.at("death_animation"), p.death_animation = "INVALID");
	//TRY_PARSE_ELSE(p.hit_animation = j.at("hit_animation"), p.hit_animation = "INVALID");

	//TRY_PARSE_ELSE(p.vulnerable_to_mario = GetsideValue(j.at("vulnerable_to_mario").get<std::string>().c_str()), p.vulnerable_to_mario = side::none);
}
