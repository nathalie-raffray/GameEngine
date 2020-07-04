#pragma once
struct RenderComponent
{
	unsigned int layer;

	static inline const char* name = "render component"; //?

};

/***************** JSON SERIALIZATION **********************/
#include "json_serialization.h"

inline void to_json(json& j, const RenderComponent& p)
{
	if(p.layer != 0) j["layer"] = p.layer;
}
inline void from_json(const json& j, RenderComponent& p)
{
	TRY_PARSE_ELSE(p.layer = j.at("layer"), p.layer = 0);
}