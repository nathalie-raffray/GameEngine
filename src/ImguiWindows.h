#pragma once
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>

using AnimationId = std::string;

struct AnimationComponent;

struct ImguiAnimation
{
	std::vector<const char*> spriteNames;
	std::vector<const char*> textureNames;
	std::unordered_map<std::string, std::vector<const char*>> associatedAnimations;
	std::vector<const char*> filePaths;
};

class ImguiWindows
{
private:
	ImguiAnimation names;
	std::shared_ptr<AnimationComponent> spLittleMario;

public:
	void animationInit();
	void animationEditor();

	void addAssociatedAnimation(std::string filePath, const AnimationId& id);
};
