#include "ImguiWindows.h"

/* IMGUI / JSON */
#include "imgui.h"
#include "imgui-SFML.h"
#include "json.hpp"
using json = nlohmann::json;

/* STL */
#include <iostream>
#include <iomanip>
#include <fstream>

/* SYSTEMS IMGUI WINDOWS IS USING */
#include "AnimationSystem.h"
#include "RenderingSystem.h"

/* ASSETS */
#include "Game.h"
#include "AssetStorage.h"

/* OTHER */
#include "AnimationCollection.h"
#include "Texture.h"
#include "Prefab.h"
#include "SystemRegistry.h"
#include "ImGuiComponents.h"


using IntRect = sf::IntRect;

//----------------------------------------------------------------------------------------------

void ImguiWindows::update()
{
	static std::vector<const char*> editors = { "sprite editor", "animation editor", "level editor" };

	ImGui::Begin("Imgui Editors");

	static int i = 0;
	ImGui::Combo("editor", &i, editors.data(), static_cast<int>(editors.size()));

	switch (i)
	{
	case 0:
		spriteEditor();
		break;
	case 1:
		animationEditor();
		break;
	case 2:
		entityEditor();
		break;
	}

	ImGui::End();
}

//----------------------------------------------------------------------------------------------

void ImguiWindows::spriteInit()
{
	imgui_sprite.entity = Prefab::get_clone("imguiSpitePrefab");
	Game::system_registry->addEntityToSystems(imgui_sprite.entity);

	for (auto& tc : Game::assets->table_of_contents)
	{
		if (tc.second.find("sprites.json") != -1)
		{
			if (imgui_sprite.sprites.count(tc.second) == 0)
			{
				imgui_sprite.filePaths.emplace_back(tc.second.c_str());
			}
			imgui_sprite.sprites[tc.second].emplace_back(tc.first.c_str());
		}
	}
}

//----------------------------------------------------------------------------------------------

void ImguiWindows::spriteEditor()
{
	if (!imgui_sprite.entity->m_Active)
	{
		imgui_sprite.entity->m_Active = true;
		Game::system_registry->addEntityToSystems(imgui_sprite.entity);
		names.entity->m_Active = false;
	}

	static int i = 0; //to choose files
	static int j = 0; //to choose sprites
	static int k = 0; //to choose textures

	static char newSpriteName[50];
	static Sprite* currSprite = Game::assets->get<Sprite>(imgui_sprite.entity->get<SpriteComponent>()->spriteId);

	static bool newSprite = false;

	if (ImGui::Combo("file", &i, imgui_sprite.filePaths.data(), static_cast<int>(imgui_sprite.filePaths.size())))
	{
		j = 0;
		imgui_sprite.entity->get<SpriteComponent>()->spriteId = imgui_sprite.sprites[imgui_sprite.filePaths[i]][j];
		currSprite = Game::assets->get<Sprite>(imgui_sprite.entity->get<SpriteComponent>()->spriteId);
		k = 0;
		//k = names.textureNames
	}

	if (ImGui::Combo("sprite", &j, imgui_sprite.sprites[imgui_sprite.filePaths[i]].data(), static_cast<int>(imgui_sprite.sprites[imgui_sprite.filePaths[i]].size())))
	{
		imgui_sprite.entity->get<SpriteComponent>()->spriteId = imgui_sprite.sprites[imgui_sprite.filePaths[i]][j];
		currSprite = Game::assets->get<Sprite>(imgui_sprite.entity->get<SpriteComponent>()->spriteId);
		k = 0;
		//k = 
	}

	if (ImGui::Button("New Sprite") || newSprite)
	{
		newSprite = true;
		ImGui::InputTextWithHint("name", "enter new sprite name", newSpriteName, 50);
		ImGui::SameLine();
		if (ImGui::Button("enter"))
		{
			Game::assets->assets.emplace(newSpriteName, std::make_unique<Sprite>());
			imgui_sprite.sprites[imgui_sprite.filePaths[i]].emplace_back(Game::assets->assets.find(newSpriteName)->first.c_str());
			imgui_sprite.entity->get<SpriteComponent>()->spriteId = newSpriteName;
			currSprite = Game::assets->get<Sprite>(newSpriteName);
			currSprite->scale = 5;
			currSprite->texId = names.textureNames[0];
			currSprite->m_sprite.setTexture(Game::assets->get<Texture>(currSprite->texId)->texture);
			currSprite->texRect = { 0, 0, 100, 100 };
			j = static_cast<int>(imgui_sprite.sprites[imgui_sprite.filePaths[i]].size() - 1);
			k = 0;
			newSprite = false;
		}
	}

	if (ImGui::Combo("texture", &k, names.textureNames.data(), static_cast<int>(names.textureNames.size())))
	{
		currSprite->texId = names.textureNames[k];
		currSprite->m_sprite.setTexture(Game::assets->get<Texture>(currSprite->texId)->texture);
	}
	if (ImGui::InputInt4("texRect", &currSprite->texRect.left))
	{
		currSprite->m_sprite.setTextureRect(currSprite->texRect);
	}
	if (ImGui::InputFloat("scale", &currSprite->scale))
	{
		currSprite->m_sprite.setScale(currSprite->scale, currSprite->scale);
	}

	if (ImGui::Button("Save?"))
	{

	}
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
	names.entity = Prefab::get_clone("imguiAnimationPrefab");
	names.entity->m_Active = false;


	//Game::system_registry->addEntityToSystems(names.entity);
	//names.entity->m_Active = false;
	
}

//----------------------------------------------------------------------------------------------

void ImguiWindows::animationEditor()
{

	//ImGui::Begin("Animation Editor");

	if (!names.entity->m_Active)
	{
		names.entity->m_Active = true;
		Game::system_registry->addEntityToSystems(names.entity);
		imgui_sprite.entity->m_Active = false;
	}

	auto spLittleMario = names.entity->get<AnimationComponent>();

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
			//Game::assets->assets.emplace()
			currentAnimationCollection->animations.emplace(std::string(newAnimationName), std::make_unique<Animation>());
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

	//ImGui::End();
}

//----------------------------------------------------------------------------------------------

void ImguiWindows::entityInit()
{
	for (auto& tc : Game::assets->table_of_contents)
	{
		if (tc.second.find("entity.assets.json") != -1)
		{
			imgui_entity.prefabs.emplace_back(tc.first.c_str());
		}

		if (tc.second.find("level.json") != -1)
		{
			json js;
			std::ifstream i(tc.second);
			i >> js;

			imgui_entity.entityfilepaths.emplace_back(js.at("entities_filepath").get<std::string>().c_str());
		}

	}
	
}
#include "Level.h"
//----------------------------------------------------------------------------------------------

#define IMGUI_COMPONENT(component) if (current_prefab)\
{\
	if (current_prefab->entity_programmable.has<component>())\
	{\
		if (ImGui::TreeNode(component::name))\
		{\
			ImGuiComponent<component>(current_entity);\
			ImGui::TreePop();\
		}\
	}\
}

void ImguiWindows::entityEditor()
{
	names.entity->m_Active = false;
	imgui_sprite.entity->m_Active = false;

	static Prefab* current_prefab = nullptr;
	static EntityHandle current_entity;

	static bool saved = false;

	static int j = 0;
	if (ImGui::Combo("filepath", &j, imgui_entity.entityfilepaths.data(), static_cast<int>(imgui_entity.entityfilepaths.size())))
	{
		//should be levels instead of filepaths
	}

	static int i = 0;
	if (ImGui::Combo("prefabs", &i, imgui_entity.prefabs.data(), static_cast<int>(imgui_entity.prefabs.size())))
	{
		current_prefab = Game::assets->get<Prefab>(imgui_entity.prefabs[i]);
		if (!saved)
		{
			if (*current_entity) {
				current_entity->m_Active = false;
			}
		}
		saved = false;

		current_entity = Game::entity_registry->create();
		//remove from systems?
		current_prefab->entity_immutable.clone(*current_entity);
		current_prefab->entity_programmable.clone(*current_entity);
		Game::system_registry->addEntityToSystems(current_entity);
	}

	//ZOOM
	static int zoom = 0;
	const ImS32 s32_one = 1;

	if (ImGui::InputScalar("zoom", ImGuiDataType_S32, &zoom, &s32_one, NULL, "%u"))
	{
		Game::current_level->camera->get<CameraComponent>()->zoom = static_cast<float>(pow(2, zoom));
	}

	//change scale of all sprites at render

	static bool ismoving = false;
	if (*current_entity)
	{
		if (current_entity->has<TransformComponent>())
		{
			if (ImGui::Button("move") || ismoving)
			{
				ismoving = true;
				current_entity->get<TransformComponent>()->pos = { static_cast<int>(ImGui::GetMousePos().x), static_cast<int>(ImGui::GetMousePos().y) };

				if (ImGui::IsMouseClicked(ImGui::GetMouseCursor()))
				{
					ismoving = false;
				}
			}
		}
	}

	IMGUI_COMPONENT(AnimationComponent);
	IMGUI_COMPONENT(SpriteComponent);
	IMGUI_COMPONENT(TransformComponent);
	//IMGUI_COMPONENT(RenderComponent);
	//IMGUI_COMPONENT(CameraComponent);

	if (ImGui::Button("Save?"))
	{
		//to_json currentEntity
		saved = true;
	}


}

//----------------------------------------------------------------------------------------------



