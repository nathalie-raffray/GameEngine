#pragma once
#include <SFML/System/Vector2.hpp>

template<typename T>
using Vector2 = sf::Vector2<T>;

struct TransformComponent
{
	Vector2<float> pos;
	Vector2<float> new_pos;
	
	float rotationz;

	float scale;

	static inline const char* name = "transform component"; 
};

/***************** JSON SERIALIZATION **********************/
#include "json_serialization.h"

inline void to_json(json& j, const TransformComponent& p)
{
	j["pos"] = p.pos;
	j["scale"] = p.scale;
	if(p.rotationz < -0.01f || p.rotationz > 0.01f) j["rotationz"] = p.rotationz;
}
inline void from_json(const json& j, TransformComponent& p)
{
	TRY_PARSE_ELSE(p.pos = j.at("pos"), p.pos = {});
	TRY_PARSE_ELSE(p.new_pos = j.at("pos"), p.new_pos = {});
	TRY_PARSE_ELSE(p.rotationz = j.at("rotationz"), p.rotationz = 0);
	TRY_PARSE_ELSE(p.scale = j.at("scale"), p.scale = 1);
}