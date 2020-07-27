#pragma once
#include "PlayerStateEnum.h"
#include "SideEnum.h"

#include <string>
using AnimationId = std::string;

struct PlayerComponent
{
	//float speed;
	player_state state;
	float hit_duration; //how much time should the animation mode be "flash"
	
	float friction; //?

	float jump_gravity;
	float high_jump_gravity;
	float fall_gravity;
	
	//Vector2<float> jum
	float jump_velocity;
	float high_jump_velocity;

	float walk_velocity;
	float run_velocity;

	//bool is_jumping = false;

	int max_jumps;
	int curr_jumps;

	AnimationId change_direction_anim;
	side change_direction_anim_side;
	//bool ishit because there is a point where player is numb to other collisions
	//bool current_hit_duration; //decrease this till it gets to 0. maybe this can be for all hitbox entities?

	//perhaps each state can spell out the name of the animationcollection
	//or each state = AnimationCollectionId once i make that a uint32 but nvm that wouldnt work
	static inline const char* name = "player component"; //?
};

/***************** JSON SERIALIZATION **********************/
#include "json_serialization.h"

inline void to_json(json& j, const PlayerComponent& p)
{
	//j["speed"] = p.speed;
	j["state"] = GetString(p.state);

	j["jump_gravity"] = p.jump_gravity;
	j["high_jump_gravity"] = p.high_jump_gravity;
	j["fall_gravity"] = p.fall_gravity;
	j["jump_velocity"] = p.jump_velocity;
	j["high_jump_velocity"] = p.high_jump_velocity;
	j["walk_velocity"] = p.walk_velocity;
	j["run_velocity"] = p.run_velocity;

	j["max_jumps"] = p.max_jumps;
	j["change_direction_anim"] = p.change_direction_anim;
}
inline void from_json(const json& j, PlayerComponent& p)
{
//	TRY_PARSE(p.speed = j.at("speed").get<float>());
	TRY_PARSE_ELSE(p.jump_gravity = j.at("jump_gravity").get<float>(), p.jump_gravity = 0);
	TRY_PARSE_ELSE(p.high_jump_gravity = j.at("high_jump_gravity").get<float>(), p.high_jump_gravity = 0);
	TRY_PARSE_ELSE(p.fall_gravity = j.at("fall_gravity").get<float>(), p.fall_gravity = 0);
	TRY_PARSE_ELSE(p.jump_velocity = j.at("jump_velocity").get<float>(), p.jump_velocity = 0);
	TRY_PARSE_ELSE(p.high_jump_velocity = j.at("high_jump_velocity").get<float>(), p.high_jump_velocity = 0);
	TRY_PARSE_ELSE(p.walk_velocity = j.at("walk_velocity").get<float>(), p.walk_velocity = 0);
	TRY_PARSE_ELSE(p.run_velocity = j.at("run_velocity").get<float>(), p.run_velocity = 0);

	TRY_PARSE_ELSE(p.max_jumps = j.at("max_jumps").get<int>(), p.max_jumps = 2);
	p.curr_jumps = 0;

	TRY_PARSE(p.change_direction_anim = j.at("change_direction_anim").get<std::string>());
	TRY_PARSE_ELSE(p.state = Getplayer_stateValue(j.at("state").get<std::string>().c_str()), p.state = player_state::little);
}