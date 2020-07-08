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
	std::vector<const char*> textureNames;
	std::unordered_map<AnimationCollectionId, std::vector<const char*>> associatedAnimations;
	std::unordered_map<std::string, AnimationCollectionId> filePathIds;
	std::vector<const char*> filePaths;

	EntityHandle entity;
};

struct ImguiEntity
{
	std::vector<const char*> prefabs;
	std::vector<const char*> filePaths;
	std::vector<const char*> levels;
};

class ImguiWindows
{
public:
	std::string toc_filepath;

	ImguiSprite imgui_sprite;
	ImguiAnimation imgui_animation;
	ImguiEntity imgui_entity;

public:

	ImguiWindows(std::string fp) : toc_filepath(fp) {}

	void init()
	{
		spriteInit();
		animationInit();
		entityInit();
	}

	void update();

private:

	void spriteInit();
	void spriteEditor();

	void animationInit();
	void animationEditor();

	void entityInit();
	void entityEditor();

};

