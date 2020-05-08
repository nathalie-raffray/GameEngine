#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

using AnimationId = std::string;

struct AnimationComponent;

#include "json.hpp"

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
	std::shared_ptr<AnimationComponent> spLittleMario;

public:
	void add(const std::shared_ptr<AnimationComponent>& sp);
	void animationInit();
	void animationEditor();

	//json js;

	//void addAssociatedAnimation(std::string filePath, const AnimationId& id);
};
