#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include "json.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <iostream>
#include <unordered_map>
#include <iomanip>

#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "AnimationSystem.h"

using json = nlohmann::json;

typedef sf::IntRect IntRect;
typedef sf::Sprite Sprite;
template <typename T>
using Vector2 = sf::Vector2<T>; //Vector<2> is equivalent to sf::Vector2<T>

typedef sf::Texture Texture;

//extern CAnimatedSprite sprite;
//extern std::vector<CAnimatedSprite*>sprites;
extern AnimationSystem as; 

extern ResourceManager resManager;

struct ImguiAnimation
{
	std::vector<const char*> spriteNames;
	std::vector<std::vector<const char*>> animationNames;
};

class ImguiWindows
{
private:
	ImguiAnimation animInfo;
	std::vector<const char*> textureNames;

public:
	json jSprites;

	void animationInit()
	{
		//called after sprites and animations are parsed from sprites.json
		//initialize spriteNames  
		std::vector<const char*> vec;
		for (CAnimatedSprite* sprite : as.sprites)
		{
			animInfo.spriteNames.push_back(sprite->m_spriteName.c_str());
		
			animInfo.animationNames.push_back(vec);

			bool first = true;
			auto it = sprite->animations.begin();
			// Iterate over the map using iterator
			while (it != sprite->animations.end())
			{
				if (first) sprite->animPlaying = &it->second;
				animInfo.animationNames.back().push_back(it->first.c_str());
				first = false;
				it++;
			}

			animInfo.animationNames.back().push_back("New Animation");
		}
		animInfo.animationNames.push_back(vec);
		animInfo.animationNames.back().push_back("New Animation");

		animInfo.spriteNames.push_back("New Sprite");

		resManager.getTextureNames(textureNames);
		
	}

	void animationEditor()
	{
		ImGui::Begin("Animation Editor");

		static int i = 0;
		static int j = 0;
		static int k = 0;

		static CAnimatedSprite* spriteChosen = as.sprites[0];
		static Animation* animationChosen = as.sprites[0]->getAnimation(animInfo.animationNames[0][0]);

		//Choose Sprite

		static const char* hint1 = "enter new sprite name";
		static char newSpriteName[50];

		static const char* hint2 = "enter new animation name";
		static char newAnimationName[50];

		static bool creatingNewSprite = false; //newSprite checks whether we are creating a new sprite
		static bool creatingNewAnimation = false;

		if (ImGui::Combo("sprite", &i, animInfo.spriteNames.data(), animInfo.spriteNames.size()))
		{
			if (creatingNewSprite) {
				as.remove(spriteChosen);
				delete spriteChosen;
				creatingNewSprite = false;
			}
			
			if (i != animInfo.spriteNames.size() - 1) { //sprite combo != "New Sprite"
				
				spriteChosen = as.sprites[i];
				spriteChosen->enable();
				if (j != animInfo.animationNames[i].size() - 1) //animation combo != "New Animation"
				{
					animationChosen = spriteChosen->animPlaying = spriteChosen->getAnimation(animInfo.animationNames[i][j]);
					std::cout << "animation name: " << animInfo.animationNames[i][j] << std::endl;
				} 
			}
			else { //sprite combo = "New Sprite"
				spriteChosen->disable();
				spriteChosen = new CAnimatedSprite;
				spriteChosen->setTexture(textureNames[k]);
				as.add(spriteChosen);
				creatingNewSprite = true;

				animationChosen = nullptr;
				creatingNewAnimation = true;
				memset(newAnimationName, 0, 50 * (sizeof newAnimationName[0])); //clear newanimationname
				memset(newSpriteName, 0, 50 * (sizeof newSpriteName[0])); //clear newspritename
			}
		}

		if (i == animInfo.spriteNames.size() - 1) ImGui::InputTextWithHint("##spritename", hint1, newSpriteName, 50); //"New Sprite"

		//Choose Animation 

		if (ImGui::Combo("animation", &j, animInfo.animationNames[i].data(), animInfo.animationNames[i].size()))
		{	
			//std::cout << "animation here i am";
			if (j != animInfo.animationNames[i].size() - 1) { //animation combo != "New Animation"
				animationChosen = spriteChosen->animPlaying = spriteChosen->getAnimation(animInfo.animationNames[i][j]);
				creatingNewAnimation = false;
			}
			else { //animation combo == "New Animation"
				animationChosen = nullptr;
				creatingNewAnimation = true;
				memset(newAnimationName, 0, 50 * (sizeof newAnimationName[0])); //clear newanimationname
			}
			spriteChosen->animPlaying = animationChosen;
		}

		if (creatingNewAnimation) {
			if (ImGui::InputTextWithHint("##animname", hint2, newAnimationName, 50))
			{
				//std::cout << "animation name imgui called" << std::endl;
			}
			ImGui::SameLine();
			if (ImGui::Button("enter"))
			{
				spriteChosen->addAnimation(newAnimationName); //could be remove
				animationChosen = spriteChosen->getAnimation(newAnimationName);
			}
		}
		//spriteChosen->animPlaying = animationChosen;

		//Choose Texture

		if (ImGui::Combo("texture", &k, textureNames.data(), textureNames.size()))
		{
			spriteChosen->setTexture(textureNames[k]);
		}

		ImGui::Separator();

		//Play Button and Frame Slider 
		static bool play = true;
		static ImGuiDir dir = ImGuiDir_Right;
		if (ImGui::ArrowButton("##play", dir))
		{
			play = !play;
			if (play) {
				spriteChosen->playAnimation();
				dir = ImGuiDir_Right;
			}
			else {
				spriteChosen->pauseAnimation();
				dir = ImGuiDir_Left;
			}
		}

		ImGui::SameLine();

		static int zero = 0;

		if (animationChosen)
			ImGui::SliderInt("Frame", &animationChosen->m_currFrame, 0, animationChosen->m_numFrames-1);
		else 
			ImGui::SliderInt("Frame", &zero, 0, 0);
		
		ImGui::Separator();

		//Animation Properties
		if (ImGui::TreeNode("Animation Properties"))
		{
			if (animationChosen)
			{
				//Animation name
				if (creatingNewAnimation) ImGui::InputText("name", newAnimationName, 50);
				else ImGui::Text(animInfo.animationNames[i][j]);

				//Enabled Checkbox
				if (ImGui::Checkbox("enabled", &spriteChosen->m_enabled));

				//Loop Checkbox
				if (ImGui::Checkbox("loop", &animationChosen->m_loop))
				{
					if (animationChosen->m_loop) spriteChosen->animPlaying = animationChosen;
				}

				ImGui::SliderInt("delay", &animationChosen->m_speed, 0, 500);

				//Change Number of Frames
				static int numFrames;
				numFrames = animationChosen->m_numFrames;
				const ImU32 u32_one = 1;
				if (ImGui::InputScalar("frameNum", ImGuiDataType_U32, &numFrames, &u32_one, NULL, "%u")) 
				{
					int difference = abs(numFrames - animationChosen->m_numFrames);
					if (numFrames > animationChosen->m_numFrames)
					{
						for (int i = 0; i < difference; ++i)
						{
							animationChosen->m_texRects.push_back({ 0,0,0,0 });
							animationChosen->m_screenRects.push_back({ 0,0,0,0 });
						}
					}else if (numFrames < animationChosen->m_numFrames)
					{
						for (int i = 0; i < difference; ++i)
						{
							animationChosen->m_texRects.pop_back();
							animationChosen->m_screenRects.pop_back();
						}
					}
					animationChosen->m_numFrames = numFrames;
				}

				ImGui::Separator();

				//TexRects -- texture offsets, width and height
				if (ImGui::TreeNode("Tex Rects"))
				{		
					for (int i = 0; i < animationChosen->m_texRects.size(); ++i)
					{
						ImGui::DragInt4(("Frame " + std::to_string(i)).c_str(), &animationChosen->m_texRects[i].left, 0, 1000);
					}
					ImGui::TreePop();
				}

				ImGui::Separator();

				//ScreenRects -- screen offsets, width and height
				if (ImGui::TreeNode("Screen Rects"))
				{
					for (int i = 0; i < animationChosen->m_screenRects.size(); ++i)
					{
						ImGui::DragInt4(("Frame " + std::to_string(i)).c_str(), &animationChosen->m_screenRects[i].left, 0, 1000);
					}
					ImGui::TreePop();
				}
				
			}
			
			ImGui::TreePop();
		}

		ImGui::Separator();

		//Save Button
		if (ImGui::Button("Save"))
		{
			json jsprite;
			json janimation;
			json jtexRects, jscreenRects;


			std::string texRectString = "[ ";

			for (IntRect& m_texRect : animationChosen->m_texRects)
			{
				texRectString += (std::string("[") + std::to_string(m_texRect.left) + ", " + std::to_string(m_texRect.top)
					+ ", " + std::to_string(m_texRect.width) + ", " + std::to_string(m_texRect.height) + "]");
				texRectString += ", ";
			}
			texRectString = texRectString.substr(0, texRectString.size() - 2); //remove last comma and space
			texRectString += " ]";
			//std::cout << texRectString << std::endl;

			jtexRects = json::parse(texRectString);
			//std::cout << jtexRects.dump(4) << std::endl;

			std::string screenRectString = "[ ";

			for (IntRect& m_screenRect : animationChosen->m_screenRects)
			{
				screenRectString += (std::string("[") + std::to_string(m_screenRect.left) + ", " + std::to_string(m_screenRect.top)
					+ ", " + std::to_string(m_screenRect.width) + ", " + std::to_string(m_screenRect.height) + "]");
				screenRectString += ", ";
			}
			screenRectString = screenRectString.substr(0, screenRectString.size() - 2); //remove last comma and space
			screenRectString += " ]";
			jscreenRects = json::parse(screenRectString);


			if (creatingNewSprite) {
				animInfo.spriteNames.pop_back();
				animInfo.spriteNames.push_back(newSpriteName);
				animInfo.spriteNames.push_back("New Sprite");
				creatingNewSprite = false;
			}
			if (creatingNewAnimation)
			{
				animInfo.animationNames[i].pop_back();
				animInfo.animationNames[i].push_back(newAnimationName);
				animInfo.animationNames[i].push_back("New Animation");
				creatingNewAnimation = false;
			}

			jSprites[i]["spriteName"] = animInfo.spriteNames[i];
			jSprites[i]["texName"] = textureNames[k];
			jSprites[i]["enabled"] = spriteChosen->isEnabled();
			jSprites[i]["animations"][j]["animName"] = animInfo.animationNames[i][j];
			jSprites[i]["animations"][j]["texRect"] = jtexRects;
			jSprites[i]["animations"][j]["screenRect"] = jscreenRects;
			jSprites[i]["animations"][j]["numFrames"] = animationChosen->m_numFrames;
			jSprites[i]["animations"][j]["speed"] = animationChosen->m_speed;
			jSprites[i]["animations"][j]["loop"] = animationChosen->m_loop;

			std::cout << jSprites.dump(4) << std::endl;

			std::ofstream o;
			o.open("../res/data/sprites.json");
			o << std::setw(4) << jSprites << std::endl;
			o.close();

			//saved = true;
		}

		//json js;

		ImGui::End();
	}
};