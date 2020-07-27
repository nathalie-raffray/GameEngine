#pragma once
struct RenderComponent
{
	unsigned int layer;
	bool worldspace; //if a rendered component is in world space, then it moves with the camera. 
	//layer renderlayer; //have layer of enemies//player//shells//blocks whatever and use those for collision

	static inline const char* name = "render component"; //?

};

/***************** JSON SERIALIZATION **********************/
#include "json_serialization.h"

inline void to_json(json& j, const RenderComponent& p)
{
	if(p.layer != 0) j["layer"] = p.layer;
	if(!p.worldspace) j["worldspace"] = p.worldspace;
}
inline void from_json(const json& j, RenderComponent& p)
{
	TRY_PARSE_ELSE(p.layer = j.at("layer"), p.layer = 0);
	TRY_PARSE_ELSE(p.worldspace = j.at("worldspace"), p.worldspace = true);
}