#pragma once
#include "Asset.h"

#include "Entity.h"
#include "SystemRegistry.h"

#include <string>
#include <stack>

//----------------------------------------------------------------------------------------------

using AssetId = std::string;
class Level;

struct LevelHandle
{
	Level* operator->() const;

	Level& operator*() const;

	AssetId level_id;
};

//----------------------------------------------------------------------------------------------

class Level : public Asset
{
public:
	static bool load(const std::string & filePath);

	static void pushLevel(LevelHandle level);

	static inline std::stack<LevelHandle> levels;

public:
	~Level() override = default;

	Level(bool s) : stackable(s) {}
	Level() {}

	bool stackable;

	EntityRegistry entity_registry; //makes sense to make them pointers maybe...
	SystemRegistry system_registry;
	EntityHandle camera;
};

//----------------------------------------------------------------------------------------------
