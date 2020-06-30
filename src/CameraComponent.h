#pragma once

template<typename T>
using Vector2 = sf::Vector2<T>;

struct CameraComponent
{
	Vector2<int> aspectRatio;
	Vector2<int> screenCoord0; //top lefthand coords
	Vector2<int> screenCoord1; //bottom righthand coords
};

/***************** JSON SERIALIZATION **********************/
#include "json_serialization.h"

inline void to_json(json& j, const CameraComponent& c)
{
	TRY_PARSE(j["aspectRatio"] = c.aspectRatio);
	TRY_PARSE(j["screenCoord0"] = c.screenCoord0);
	TRY_PARSE(j["screenCoord1"] = c.screenCoord1);
}
inline void from_json(const json& j, CameraComponent& c)
{
	TRY_PARSE(c.aspectRatio = j.at("aspectRatio"));
	TRY_PARSE(c.screenCoord0 = j.at("screenCoord0"));
	TRY_PARSE(c.screenCoord1 = j.at("screenCoord1"));
}