#pragma once
#include <SFML/System/Vector2.hpp>

template<typename T>
using Vector2 = sf::Vector2<T>;

struct TransformComponent
{
	Vector2<int> pos;
	//Vector2<int> new_pos;
	
	float rotationz;

	static inline const char* name = "transform component"; //?
};

/***************** JSON SERIALIZATION **********************/
#include "json_serialization.h"

inline void to_json(json& j, const TransformComponent& p)
{
	j["pos"] = p.pos;
	if(p.rotationz < -0.01f || p.rotationz > 0.01f) j["rotationz"] = p.rotationz;
}
inline void from_json(const json& j, TransformComponent& p)
{
	TRY_PARSE_ELSE(p.pos = j.at("pos"), p.pos = {});
	TRY_PARSE_ELSE(p.rotationz = j.at("rotationz"), p.rotationz = 0);
}