#pragma once
#include <string>
using AssetId = std::string;

struct PrefabComponent
{
	//char entity_asset_id[50];
	AssetId prefab_id;

	//or have a bitset of maxcomponents to see which one is programmable
};

/***************** JSON SERIALIZATION **********************/
#include "json_serialization.h"

inline void to_json(json& j, const PrefabComponent& c)
{
	j["prefab_id"] = static_cast<std::string>(c.prefab_id);
}
inline void from_json(const json& j, PrefabComponent& c)
{
	//TRY_PARSE(strcpy_s(c.entity_asset_id, j["prefab_id"].get<std::string>().c_str()));
	c.prefab_id = j.at("prefab_id").get<std::string>();
}
