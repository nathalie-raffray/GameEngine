#pragma once
#include "SideEnum.h"

struct HitboxComponent
{
	side vulnerable_to_player; //if that side is hit, then if it has a health component, decrease health && play appropriate animations, do collision resolution
								//for player this would be side::none
	
	int damage_to_other;
	bool takes_partial_damage; //for those blocks that don't lose health after little mario jumps at them (but hit animation plays). also cloud blocks. 
	//bool takes_damage; //for when mario becomes a star, when koopa becomes a shell. maybe we can assume that once an entity doesnt 
						//have a health component it doesn't take damage

	AnimationId death_animation; //useful for question blocks, goomba, mario,
	AnimationId hit_animation; //maybe put this directly in the asset animationcollection?

	bool ishit;
	float hit_duration; //how much time should the animation mode be "flash" for player/how long should it not react to other collisions
	float current_hit_time;

	//side attack_side;
	//can use this for blocks as well 
	//bool vulnerable_to_shell; //seems like all trigger static colliders are vulnerable to shell. so i could take this away. 

	static inline const char* name = "hitbox component";

};

/***************** JSON SERIALIZATION **********************/
#include "json_serialization.h"

inline void to_json(json& j, const HitboxComponent& p)
{
	if (p.vulnerable_to_player != side::none) j["vulnerable_to_player"] = GetString(p.vulnerable_to_player);
	//if (p.vulnerable_to_shell) j["vulnerable_to_shell"] = p.vulnerable_to_shell;
}
inline void from_json(const json& j, HitboxComponent& p)
{
	TRY_PARSE_ELSE(p.vulnerable_to_player = GetsideValue(j.at("vulnerable_to_player").get<std::string>().c_str()), p.vulnerable_to_player = side::none);
	//TRY_PARSE_ELSE(p.vulnerable_to_shell = j.at("vulnerable_to_shell").get<bool>(), p.vulnerable_to_shell = false);
}
