#include "imgui.h"
#include "imgui-SFML.h"
#include "json.hpp"

#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <unordered_map>
#include <iomanip>

#include "ImguiWindows.h"
#include "AssetStorage.h"
#include "SpriteComponent.h"
#include "AnimationSystem.h"
#include "RenderingSystem.h"
#include "Sprite.h"

using json = nlohmann::json;

using IntRect = sf::IntRect;
using Texture = sf::Texture;

//----------------------------------------------------------------------------------------------

void ImguiWindows::animationInit()
{

	spLittleMario = std::make_shared<AnimationComponent>("littlemario_walk");
	Game::animationSystem->add(spLittleMario);
	Game::renderingSystem->add(spLittleMario);

	for (auto& sprite : Game::assets->sprites)
	{
		names.spriteNames.emplace_back(sprite.first.c_str());
	}
	for (auto& animation : Game::assets->animations)
	{
		names.animationNames.emplace_back(animation.first.c_str());
	}
	for (auto& texture : Game::assets->textures)
	{
		names.textureNames.emplace_back(texture.first.c_str());
	}

	std::cout << names.textureNames[0] << std::endl;
}

//----------------------------------------------------------------------------------------------

void ImguiWindows::animationEditor()
{
	ImGui::Begin("Animation Editor");
	static int i = 0;

	static std::string animationChosen = names.animationNames[0];
	static int numFrames = static_cast<int>(Game::assets->getAnimation(animationChosen)->frames.size());

	//Choose Animation
	static char newAnimationName[50];
	static char newSpriteName[50];

	static bool creatingNewAnimation = false; //newSprite checks whether we are creating a new sprite

	static std::vector<bool> creatingNewSprite(numFrames);

	static Animation animationCopy;

	static bool init = false;

	if (ImGui::Combo("animation", &i, names.animationNames.data(), static_cast<int>(names.animationNames.size())))
	{
		if (creatingNewAnimation) {
			creatingNewAnimation = false;
		}
		animationChosen = names.animationNames[i];
		spLittleMario->currentAnimation = animationChosen;
		numFrames = static_cast<int>(Game::assets->getAnimation(animationChosen)->frames.size());

		Game::assets->getAnimation(animationChosen)->frames.resize(numFrames);
		spLittleMario->currentFrame = 0;
		init = false;
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
			Game::assets->addAnimation(newAnimationName);
			names.animationNames.emplace_back(newAnimationName);
			animationChosen = newAnimationName;
			spLittleMario->currentAnimation = animationChosen;
			spLittleMario->currentFrame = 0;
			i = static_cast<int>(names.animationNames.size() - 1);

			numFrames = 0;
			Game::assets->getAnimation(animationChosen)->frames.resize(0);
			//sprites.resize(0);
		}
		ImGui::NewLine();
	}
	ImGui::SameLine();

	if (ImGui::Button("Remove Animation"))
	{
		Game::assets->removeAnimation(names.animationNames[i]);
		names.animationNames.erase(names.animationNames.begin() + i);
		i = 0;
		animationChosen = names.animationNames[0];
		spLittleMario->currentAnimation = animationChosen;
		memset(newAnimationName, 0, 50);
		creatingNewAnimation = false;
	}

	ImGui::Separator();
	static int j = 0;
	static const char* modes[] = { "loop", "one time", "ping pong" };
	if (ImGui::Combo("mode", &j, modes, 3))
	{
		auto& mode = Game::assets->getAnimation(spLittleMario->currentAnimation)->mode;
		switch (j)
		{
		case 0:
			mode = Animation::loop;
			break;
		case 1:
			mode = Animation::one_time;
			break;
		case 2:
			mode = Animation::ping_pong_forward;
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

	newNumFrames = numFrames;
	if (ImGui::InputScalar("frameNum", ImGuiDataType_U32, &newNumFrames, &u32_one, NULL, "%u"))
	{
		int difference = abs(numFrames - newNumFrames);
		if (newNumFrames > numFrames)
		{
			for (int ii = 0; ii < difference; ++ii)
			{
				if (spLittleMario->currentFrame > newNumFrames)
				{
					spLittleMario->currentFrame = newNumFrames - 1;
				}
				creatingNewSprite.push_back(false);
				Game::assets->getAnimation(animationChosen)->frames.emplace_back(names.spriteNames[0]);
			}
		}
		else if (newNumFrames < numFrames)
		{
			auto& frames = Game::assets->getAnimation(spLittleMario->currentAnimation)->frames;
			for (int ii = 0; ii < difference; ++ii)
			{
				frames.pop_back();
				creatingNewSprite.pop_back();
			}
		}
		numFrames = newNumFrames;

	}

	ImGui::Separator();

	static std::vector<int> k(numFrames);
	/*initialize k*/
	k.resize(numFrames);
	if (!init)
	{
		for (int n = 0; n < numFrames; ++n)
		{
			AnimationFrame& frame = Game::assets->getAnimation(animationChosen)->frames[n];
			const char* id = frame.spriteId.c_str();
			std::vector<const char*>::iterator it = std::find_if(names.spriteNames.begin(), names.spriteNames.end(), [id](const char* str) {
				if (strcmp(str, id) == 0)
					return true;
				return false;
			});
			int index = static_cast<int>(std::distance(names.spriteNames.begin(), it));
			k[n] = index;
		}
		init = true;
	}

	static std::vector<int> l(numFrames);
	l.resize(numFrames);

	creatingNewSprite.resize(numFrames);

	for (int n = 0; n < numFrames; n++)
	{
		if (ImGui::TreeNode(("Frame" + std::to_string(n)).c_str()))
		{
			if (ImGui::Combo("sprites", &k[n], names.spriteNames.data(), static_cast<int>(names.spriteNames.size())))
			{
				Game::assets->getAnimation(animationChosen)->frames[n].spriteId = names.spriteNames[k[n]];
			}
			if (ImGui::Button("New Sprite"))
			{
				creatingNewSprite[n] = true;
			}
			if (creatingNewSprite[n])
			{
				ImGui::InputTextWithHint("name", "enter new sprite name", newSpriteName, 50);
				if (ImGui::Button("enter"))
				{
					Game::assets->addSprite(newSpriteName, std::make_unique<Sprite>());
					names.spriteNames.emplace_back(Game::assets->sprites.find(newSpriteName)->first.c_str()); // TO MAKE A COPY
					Game::assets->getAnimation(animationChosen)->frames[n].spriteId = newSpriteName;
					//give it a random texture
					Sprite* newSprite = Game::assets->getSprite(newSpriteName);
					newSprite->texId = names.textureNames[0];
					l[n] = 0; //make the combo select the first texture
					newSprite->m_sprite.setTexture(*Game::assets->getTexture(newSprite->texId));
					k[n] = static_cast<int>(names.spriteNames.size() - 1); //make the combo select the new sprite.

					memset(newSpriteName, 0, 50);
					creatingNewSprite[n] = false;

					std::cout << Game::assets->getAnimation(animationChosen)->frames[n].spriteId << std::endl;
					std::cout << *names.spriteNames[names.spriteNames.size() - 1] << std::endl;
				}
				ImGui::NewLine();
			}
			ImGui::SameLine();
			if (ImGui::Button("Remove Sprite"))
			{
				Game::assets->removeSprite(names.spriteNames[k[n]]);
				names.spriteNames.erase(names.spriteNames.begin() + k[n]);
				for (int ii = 0; ii < k.size(); ++ii)
				{
					if (k[ii] > k[n])
					{
						k[ii]--;
					}
				}
				k[n] = 0;
				Game::assets->getAnimation(animationChosen)->frames[n].spriteId = names.spriteNames[0];

				spLittleMario->currentFrame = 0;

				memset(newSpriteName, 0, 50);
				creatingNewSprite[n] = false;
			}
			Sprite* currSprite = Game::assets->getSprite(Game::assets->getAnimation(animationChosen)->frames[n].spriteId);
			if (currSprite && !creatingNewSprite[n]) //check if spriteid exists
			{
				if (ImGui::Combo("texture", &l[n], names.textureNames.data(), static_cast<int>(names.textureNames.size())))
				{
					currSprite->texId = names.textureNames[l[n]];
					currSprite->m_sprite.setTexture(*Game::assets->getTexture(currSprite->texId));
				}
				if (ImGui::InputInt4("texRect", &currSprite->texRect.left))
				{
					currSprite->m_sprite.setTextureRect(currSprite->texRect);
				}
				if (ImGui::InputFloat("scale", &currSprite->scale))
				{
					currSprite->m_sprite.setScale(currSprite->scale, currSprite->scale);
				}
				ImGui::InputFloat("duration", &Game::assets->getAnimation(spLittleMario->currentAnimation)->frames[n].duration);
			}

			ImGui::TreePop();
		}
		/**/
	}

	if (ImGui::Button("Save?"))
	{

	}

	ImGui::End();
}

//----------------------------------------------------------------------------------------------

void ImguiWindows::addFilePath(std::string filePath)
{
	names.filePaths.emplace_back(filePath.c_str());
	//names.animationJsons[filePath] = std::move(aj);
}

//----------------------------------------------------------------------------------------------