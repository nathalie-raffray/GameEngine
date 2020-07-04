#pragma once
#include "Entity.h"
#include "Prefab.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include "ImguiWindows.h"

template<class T>
void ImGuiComponent(EntityHandle eh) {};

template<>
void ImGuiComponent<AnimationComponent>(EntityHandle eh)
{
	static std::string currentAnimation = eh->get<AnimationComponent>()->currentAnimation;
	static AnimationCollection* currentAnimationCollection = Game::assets->get<AnimationCollection>(eh->get<AnimationComponent>()->animation_collection_id);
	static auto animationNames = Game::imguiWin->names.associatedAnimations[eh->get<AnimationComponent>()->animation_collection_id];

	static bool changeAnimation = false;

	//Choose File
	static int k = 0;
	static int i = 0;
	if (ImGui::Combo("file", &k, Game::imguiWin->names.filePaths.data(), static_cast<int>(Game::imguiWin->names.filePaths.size())))
	{
		std::string& newAnimationCollectionID = Game::imguiWin->names.filePathIds[Game::imguiWin->names.filePaths[k]];
		eh->get<AnimationComponent>()->animation_collection_id = newAnimationCollectionID;
		animationNames = Game::imguiWin->names.associatedAnimations[newAnimationCollectionID];
		currentAnimationCollection = Game::assets->get<AnimationCollection>(newAnimationCollectionID);
		i = 0;
		//numFrames = 0;
		changeAnimation = true;
		/*memset(newFileName, 0, 50);
		memset(newAnimationCollectionName, 0, 50);
		memset(newAnimationName, 0, 50);

		creatingNewFile = false;
		creatingNewAnimation = false;*/
	}

	if (ImGui::Combo("animation", &i, animationNames.data(), static_cast<int>(animationNames.size())) || changeAnimation)
	{
		changeAnimation = false;

		eh->get<AnimationComponent>()->currentFrame = 0;

		currentAnimation = animationNames[i];
		eh->get<AnimationComponent>()->currentAnimation = currentAnimation;
		//memset(newAnimationName, 0, 50);

		/*if (animationNames.size() != 0) //animationNames is 0 when there is 0 animation frames
		{
			currentAnimation = animationNames[i];
			eh->get<AnimationComponent>()->currentAnimation = currentAnimation;
			//numFrames = static_cast<int>(currentAnimationCollection->animations[currentAnimation]->frames.size());
		}*/
	}


	
	/*static char animationCollectionId[50];
	if (ImGui::InputText("animation collection id", animationCollectionId, 50))
	{
		eh->get<AnimationComponent>()->animation_collection_id = animationCollectionId;
		eh->get<AnimationComponent>()->currentFrame = 0;
	}
	static char animationId[50];
	if (ImGui::InputText("first animation id", animationId, 50))
	{
		eh->get<AnimationComponent>()->currentAnimation = animationId;
		eh->get<AnimationComponent>()->currentFrame = 0;
	}*/
};

template<>
void ImGuiComponent<SpriteComponent>(EntityHandle eh)
{
	static char spriteId[50];
	if (ImGui::InputText("sprite id", spriteId, 50))
	{
		eh->get<SpriteComponent>()->spriteId = spriteId;
	}
};

template<>
void ImGuiComponent<TransformComponent>(EntityHandle eh)
{
	ImGui::InputInt2("position", &eh->get<TransformComponent>()->pos.x);
	ImGui::InputFloat("rotation z", &eh->get<TransformComponent>()->rotationz);
};