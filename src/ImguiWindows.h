#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

#include "Entity.h"
#include "EntityRegistry.h"

#include "json.hpp"

using AnimationId = std::string;

struct AnimationComponent;

using json = nlohmann::json;
using AnimationCollectionId = std::string;

struct ImguiAnimation
{
	//std::vector<const char*> spriteNames;
	std::vector<const char*> textureNames;
	std::unordered_map<AnimationCollectionId, std::vector<const char*>> associatedAnimations;
	std::unordered_map<std::string, AnimationCollectionId> filePathIds;

	std::vector<const char*> filePaths;
};

class ImguiWindows
{
private:
	ImguiAnimation names;
	EntityHandle entity;

public:
	void add(EntityHandle eh);
	void animationInit();
	void animationEditor();

};
