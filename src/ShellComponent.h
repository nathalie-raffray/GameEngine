#pragma once
#include "PlayerStateEnum.h"

struct ShellComponent
{
	//float speed;

	//shell state 
	player_state state;
	//float hit_duration; //how much time should the animation mode be "flash"
	int friction;

	//perhaps each state can spell out the name of the animationcollection
	//or each state = AnimationCollectionId once i make that a uint32 but nvm that wouldnt work

	static inline const char* name = "shell component"; //?
};

/***************** JSON SERIALIZATION **********************/
#include "json_serialization.h"

inline void to_json(json& j, const ShellComponent& p)
{
	//j["speed"] = p.speed;
	j["state"] = GetString(p.state);
}
inline void from_json(const json& j, ShellComponent& p)
{
	//	TRY_PARSE(p.speed = j.at("speed").get<float>());
	TRY_PARSE_ELSE(p.state = Getplayer_stateValue(j.at("state").get<std::string>().c_str()), p.state = player_state::little);
}