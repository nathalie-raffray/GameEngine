#pragma once
#include "Prefab.h"
#include "AssetStorage.h"
#include <fstream>

bool Prefab::load(const std::string& filePath)
{
	json js;
	std::ifstream i(filePath);
	i >> js;

	for (auto& j : js["entities"])
	{
		auto uS = std::make_unique<Prefab>();

		*uS = j;

		Game::assets->assets.emplace(j["prefabId"].get<std::string>(), std::move(uS));
	}
	return true;
}

void to_json(json& j, const Prefab& p)
{
	j["prefabId"] = p.id;
	j["immutable_components"] = p.entity_immutable; 
	j["programmable_components"] = p.entity_programmable; 
}

void from_json(const json& j, Prefab& p)
{
	p.id = j.at("prefabId").get<std::string>();
	p.entity_immutable = j.at("immutable_components");
	p.entity_programmable = j.at("programmable_components");
}