#include "imgui.h"
#include "imgui-SFML.h"
#include "json.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <iomanip>
#include <fstream>

#include "ImguiWindows.h"
#include "AssetStorage.h"
#include "SpriteComponent.h"
#include "AnimationSystem.h"
#include "RenderingSystem.h"
#include "Sprite.h"
#include "AnimationCollection.h"
#include "Texture.h"
#include "Game.h"
#include "AnimationComponent.h"
#include "Animation.h"
#include "AnimationFrame.h"

using json = nlohmann::json;

using IntRect = sf::IntRect;

//----------------------------------------------------------------------------------------------

void ImguiWindows::add(EntityHandle eh)
{
	entity = eh;
}

//----------------------------------------------------------------------------------------------

void ImguiWindows::animationInit()
{
	for (auto& tc : Game::assets->table_of_contents)
	{
		if (tc.second.find("animations.json") != -1)
		{
			names.filePaths.emplace_back(tc.second.c_str());
			names.filePathIds[tc.second] = tc.first;

			AnimationCollection* ac = Game::assets->get<AnimationCollection>(tc.first);
			for (auto& animation : ac->animations)
			{
				names.associatedAnimations[tc.first].emplace_back(animation.first.c_str());
			}
		}
		else if (tc.second.find("textures.json") != -1)
		{
			names.textureNames.emplace_back(tc.first.c_str());
		}
	}
}

//----------------------------------------------------------------------------------------------


void ImguiWindows::animationEditor()
{

	ImGui::Begin("Animation Editor");

	auto spLittleMario = entity->get<AnimationComponent>();

	static int k = 0; //to choose files
	static int i = 0; //to choose animations
	static int j = 0; //to choose modes

	static char newAnimationName[50];
	static char newFileName[50];
	static char newAnimationCollectionName[50];

	static bool creatingNewAnimation = false; //newSprite checks whether we are creating a new sprite
	static bool creatingNewFile = false;

	static auto animationNames = names.associatedAnimations[spLittleMario->animation_collection_id];

	static std::string currentAnimation = spLittleMario->currentAnimation;
	static AnimationCollection* currentAnimationCollection = Game::assets->get<AnimationCollection>(spLittleMario->animation_collection_id);

	static int numFrames = static_cast<int>(currentAnimationCollection->animations[currentAnimation]->frames.size());

	static bool changeAnimation = false;

	//Choose File
	if (ImGui::Combo("file", &k, names.filePaths.data(), static_cast<int>(names.filePaths.size())))
	{
		std::string& newAnimationCollectionID = names.filePathIds[names.filePaths[k]];
		spLittleMario->animation_collection_id = newAnimationCollectionID;
		animationNames = names.associatedAnimations[newAnimationCollectionID];
		currentAnimationCollection = Game::assets->get<AnimationCollection>(newAnimationCollectionID);
		i = 0;
		numFrames = 0;
		changeAnimation = true;
		memset(newFileName, 0, 50);
		memset(newAnimationCollectionName, 0, 50);
		memset(newAnimationName, 0, 50);

		creatingNewFile = false;
		creatingNewAnimation = false;
	}

	if (ImGui::Button("New File"))
	{
		creatingNewFile = true;
		creatingNewAnimation = false;
		memset(newAnimationName, 0, 50);
		memset(newFileName, 0, 50);
		memset(newAnimationCollectionName, 0, 50);
	}
	if (creatingNewFile)
	{
		ImGui::InputTextWithHint("file path", "enter new file path", newFileName, 50);
		ImGui::InputTextWithHint("animationCollectionId", "enter new animationCollectionId", newAnimationCollectionName, 50);
		if (ImGui::Button("enter"))
		{
			Game::assets->assets.emplace(newAnimationCollectionName, std::make_unique<AnimationCollection>());
			//names.filePaths.emplace_back(newFileName);
			//strcpy(names.filePaths.back(), newFileName);
			names.filePathIds.emplace(std::string(newFileName), std::string(newAnimationCollectionName));
			names.filePaths.emplace_back(names.filePathIds.find(newFileName)->first.c_str());
			names.associatedAnimations.emplace(newAnimationCollectionName, std::vector<const char*>(0));
			animationNames = names.associatedAnimations[newAnimationCollectionName];

			currentAnimationCollection = Game::assets->get<AnimationCollection>(newAnimationCollectionName);
			currentAnimation = "No Animation";

			k = static_cast<int>(names.filePaths.size()) - 1;
			i = 0;
			numFrames = 0;
			spLittleMario->animation_collection_id = newAnimationCollectionName;
			spLittleMario->currentAnimation = currentAnimation;
			spLittleMario->currentFrame = 0;

			creatingNewFile = false;
		}
	}

	//Choose Animation
	if (ImGui::Combo("animation", &i, animationNames.data(), static_cast<int>(animationNames.size())) || changeAnimation)
	{
		changeAnimation = false;

		if (creatingNewAnimation) {
			creatingNewAnimation = false; //dont think i need this
		}

		spLittleMario->currentFrame = 0;
		memset(newAnimationName, 0, 50);

		if (animationNames.size() != 0) //animationNames is 0 when there is 0 animation frames
		{
			currentAnimation = animationNames[i];
			spLittleMario->currentAnimation = currentAnimation;
			numFrames = static_cast<int>(currentAnimationCollection->animations[currentAnimation]->frames.size());
		}
	}
	if (ImGui::Button("New Animation"))
	{
		creatingNewAnimation = true;
	}
	if (creatingNewAnimation)
	{
		ImGui::InputTextWithHint("name", "enter new animation name", newAnimationName, 50);
		ImGui::SameLine();
		if (ImGui::Button("enter"))
		{
			currentAnimationCollection->animations.emplace(newAnimationName, std::make_unique<Animation>());
			names.associatedAnimations[spLittleMario->animation_collection_id].emplace_back(currentAnimationCollection->animations.find(newAnimationName)->first.c_str()); 
			animationNames.emplace_back(currentAnimationCollection->animations.find(newAnimationName)->first.c_str()); 
																																										  
			currentAnimation = newAnimationName;
			spLittleMario->currentAnimation = currentAnimation;
			spLittleMario->currentFrame = 0;
			i = static_cast<int>(animationNames.size() - 1);

			numFrames = 0;
			currentAnimationCollection->animations[currentAnimation]->frames.resize(0); //is this necessary?
			currentAnimationCollection->animations[currentAnimation]->mode = static_cast<animation_mode>(j);
		}
		ImGui::NewLine();
	}
	ImGui::SameLine();

	if (ImGui::Button("Remove Animation") && currentAnimationCollection->animations.size() > 0)
	{
		currentAnimationCollection->animations.erase(currentAnimation);
		animationNames.erase(animationNames.begin() + i);
		names.associatedAnimations[names.filePaths[k]].erase(names.associatedAnimations[names.filePaths[k]].begin() + i);
		i = 0;
		if (animationNames.size() == 0)
		{
			currentAnimation = "No Animation";
			numFrames = 0;
		}
		else {
			currentAnimation = animationNames[0];
			numFrames = static_cast<int>(currentAnimationCollection->animations[currentAnimation]->frames.size());
		}

		spLittleMario->currentAnimation = currentAnimation;

		memset(newAnimationName, 0, 50);
		creatingNewAnimation = false;
	}
	ImGui::Separator();
	if (currentAnimationCollection->animations.size() == 0)
	{
		ImGui::End();
		return;
	}
	static const char* modes[] = { "loop", "one time", "ping pong" };
	if (ImGui::Combo("mode", &j, modes, 3))
	{
		auto& mode = currentAnimationCollection->animations[currentAnimation]->mode;

		switch (j)
		{
		case 0:
			mode = animation_mode::loop;
			break;
		case 1:
			mode = animation_mode::one_time;
			break;
		case 2:
			mode = animation_mode::ping_pong_forward;
			break;
		}
	}
	ImGui::SameLine();
	if (ImGui::ArrowButton("Play", ImGuiDir_Right))
	{
		Game::paused = !Game::paused;
	}

	//Change Number of Frames
	static int newNumFrames = numFrames;
	const ImU32 u32_one = 1;
	
	static std::vector<int> l(numFrames); //l keeps track of texture name index for each sprite

	newNumFrames = numFrames;
	if (ImGui::InputScalar("frameNum", ImGuiDataType_U32, &newNumFrames, &u32_one, NULL, "%u"))
	{
		int difference = abs(numFrames - newNumFrames);
		auto& frames = currentAnimationCollection->animations[currentAnimation]->frames;

		if (newNumFrames > numFrames)
		{
			for (int ii = 0; ii < difference; ++ii)
			{
				frames.emplace_back(); 
				l.emplace_back(0);
			}
		}
		else if (newNumFrames < numFrames)
		{
			for (int ii = 0; ii < difference; ++ii)
			{
				frames.pop_back();
				spLittleMario->currentFrame = 0;
			}
		}
		numFrames = newNumFrames;
	}
	ImGui::Separator();

	l.resize(numFrames);

	//Change Sprites
	for (int n = 0; n < numFrames; n++)
	{
		if (ImGui::TreeNode(("Frame" + std::to_string(n)).c_str()))
		{
			AnimationFrame& currFrame = currentAnimationCollection->animations[currentAnimation]->frames[n];
			Sprite& currSprite = currFrame.sprite;

			if (ImGui::Combo("texture", &l[n], names.textureNames.data(), static_cast<int>(names.textureNames.size())))
			{
				currSprite.texId = names.textureNames[l[n]];
				currSprite.m_sprite.setTexture(Game::assets->get<Texture>(currSprite.texId)->texture);
			}
			if (ImGui::InputInt4("texRect", &currSprite.texRect.left))
			{
				currSprite.m_sprite.setTextureRect(currSprite.texRect);
			}
			if (ImGui::InputInt("screenOffsetX", &currFrame.screenOffsetX))// || ImGui::InputInt("screenOffsetY", &currFrame.screenOffsetY))
			{
				currSprite.m_sprite.setPosition(static_cast<float>(currFrame.screenOffsetX), static_cast<float>(currFrame.screenOffsetY));
			}
			if (ImGui::InputInt("screenOffsetY", &currFrame.screenOffsetY))
			{
				currSprite.m_sprite.setPosition(static_cast<float>(currFrame.screenOffsetX), static_cast<float>(currFrame.screenOffsetY));
			}
			if (ImGui::InputFloat("scale", &currSprite.scale))
			{
				currSprite.m_sprite.setScale(currSprite.scale, currSprite.scale);
			}
			ImGui::InputFloat("duration", &currFrame.duration);

			ImGui::TreePop();
		}
	}

	//Save Changes 

	if (ImGui::Button("Save?"))
	{
		json jout;
		jout = *currentAnimationCollection;
		jout["animationCollectionId"] = spLittleMario->animation_collection_id;

		std::cout << jout.dump(4) << std::endl;

		json js;
		std::ifstream is("../res/data/tableofcontents.json");
		is >> js;

		js["animations"][spLittleMario->animation_collection_id] = names.filePaths[k];

		std::cout << js.dump(4) << std::endl;

		/*
		std::ofstream o;
		o.open(names.filePaths[k]);
		o << std::setw(4) << jout << std::endl;
		o.close()

		o.open(../res/data/tableofcontents.json);
		o << std::setw(4) << js << std::endl;
		o.close()
		*/
	}

	ImGui::End();
}

//----------------------------------------------------------------------------------------------

