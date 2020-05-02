#pragma once
#include <vector>
#include <memory>

struct AnimationComponent;

struct ImguiAnimation
{
	std::vector<const char*> spriteNames;
	std::vector<const char*> animationNames;
	std::vector<const char*> textureNames;

	std::vector<const char*> filePaths;
	//std::unordered_map<std::string, json> animationJsons;
};

class ImguiWindows
{
private:
	ImguiAnimation names;
	std::shared_ptr<AnimationComponent> spLittleMario;

public:

	void animationInit();
	void animationEditor();

	void addFilePath(std::string filePath);
};
