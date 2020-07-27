#pragma once
#include <SFML/System/Vector2.hpp>

template<typename T>
using Vector2 = sf::Vector2<T>;

struct RigidBodyComponent
{
	enum direction
	{
		left = true, right = false
	};
	direction direction; //is it moving left or right in this frame 
		//can change horizontal direction by manipulating texRect.
		//change direction: (add texRect.width to texRect.x and then do texRect.width*-1)

		//(can be used as starting direction for ai, or which way mario faces).
		//note: even a paragoomba or koopa paratroopa which hops, moves only left or right essentially.
	Vector2<float> velocity;
	bool is_kinematic;

	float gravity;
	float friction;

	//    float speed;
	//rotation?
	enum fall_type
	{
		discrete, continuous, disabled //goombas fall discretely, red shells fall with physics as does mario
	};
	fall_type fall_type;

	static inline const char* name = "rigidbody component"; 
};

/***************** JSON SERIALIZATION **********************/
#include "json_serialization.h"

inline void to_json(json& j, const RigidBodyComponent& p)
{
	j["velocity"] = p.velocity;
	j["gravity"] = p.gravity;
	j["friction"] = p.friction;
	j["direction"] = static_cast<bool>(p.direction);
	j["is_kinematic"] = p.is_kinematic;
	switch (p.fall_type)
	{
	case RigidBodyComponent::discrete:
		j["fall_type"] = "discrete";
		break;
	case RigidBodyComponent::continuous:
		j["fall_type"] = "continuous";
		break;
	case RigidBodyComponent::disabled:
		j["fall_type"] = "disabled";
		break;
	}
}
inline void from_json(const json& j, RigidBodyComponent& p)
{
	TRY_PARSE_ELSE(p.velocity = j.at("velocity"), p.velocity = {});
	TRY_PARSE_ELSE(p.friction = j.at("friction"), p.friction = 1.5f);
	TRY_PARSE_ELSE(p.gravity = j.at("gravity").get<float>(), p.gravity = 0);
	TRY_PARSE_ELSE(p.is_kinematic = j.at("is_kinematic"), p.is_kinematic = false);
	TRY_PARSE_ELSE(
	if (j.at("direction").get<bool>() == true) { 
		p.direction = RigidBodyComponent::direction::left;
	}
	else {
		p.direction = RigidBodyComponent::direction::right;
	}, 
		p.direction = RigidBodyComponent::direction::left);
	
	TRY_PARSE_ELSE(
	if (j.at("fall_type").get<std::string>() == "discrete")
	{
		p.fall_type = RigidBodyComponent::discrete;
	}
	else if (j.at("fall_type").get<std::string>() == "continuous")
	{
		p.fall_type = RigidBodyComponent::continuous;
	}, p.fall_type = RigidBodyComponent::disabled);

}