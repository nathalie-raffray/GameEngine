#pragma once
#include "Asset.h"
#include "Entity.h"

#include "json_serialization.h"

#include <string>

#include "Game.h"

struct Prefab : Asset
{
public:
	Entity entity_immutable;
	Entity entity_programmable; //these two entities with their mutually exclusive components make up one entity

	std::string id;

public:
	static bool load(const std::string& filePath);

	static EntityHandle get_clone(const std::string& prefabId);
};

void to_json(json& j, const Prefab& p);
void from_json(const json& j, Prefab& p);