#pragma once
#include <string>
#include "json.hpp"

#include "ComponentPunchCard.h"

using nlohmann::json;

//template<typename T, T, ....>
class Entity : public ComponentPunchCard
{
	//clone function
public:

	std::string& name()
	{
		return m_name;
	}

	bool is_active() const { return m_isActive; }

	void set_active(bool val) { m_isActive = val; }

private:
	bool m_isActive;
	std::string m_name;
};

void to_json(json& j, const Entity& p);
void from_json(const json& j, Entity& p);