#pragma once
#include "Asset.h"

#include "Entity.h"
#include "SystemRegistry.h"

#include <string>
#include <stack>

using AssetId = std::string;

class Level : public Asset
{
public:
	static bool load(const std::string & filePath);

	static void pushLevel(const AssetId& level);

	static inline std::stack<AssetId> levels;

public:
	~Level() override = default;

	Level(bool s) : stackable(s) {}
	Level() {}

	bool stackable;

	EntityRegistry entity_registry; //makes sense to make them pointers maybe...
	SystemRegistry system_registry;
};