#pragma once
#include <vector>
#include <unordered_map>
#include <string>

#include "Entity.h"
#include "EntityRegistry.h"

#include "json_serialization.h"

using AnimationId = std::string;
using AnimationCollectionId = std::string;

struct AnimationComponent;

struct ImguiSprite
{
	std::unordered_map<std::string, std::vector<const char*>> sprites;
	std::vector<const char*> filePaths;

	EntityHandle entity;
};

struct ImguiAnimation
{
	//std::vector<const char*> spriteNames;
	std::vector<const char*> textureNames;
	std::unordered_map<AnimationCollectionId, std::vector<const char*>> associatedAnimations;
	std::unordered_map<std::string, AnimationCollectionId> filePathIds;
	std::vector<const char*> filePaths;

	EntityHandle entity;
};

struct ImguiEntity
{
	std::vector<const char*> prefabs;
	std::vector<const char*> entityfilepaths;
};

class ImguiWindows
{
public:
	ImguiSprite imgui_sprite;
	ImguiAnimation names;
	ImguiEntity imgui_entity;

	//EntityHandle entity;

public:

	void init()
	{
		spriteInit();
		animationInit();
		entityInit();
	}

	//void add(EntityHandle eh);

	void update();

	void spriteInit();
	void spriteEditor();

	void animationInit();
	void animationEditor();

	void entityInit();
	void entityEditor();

};

