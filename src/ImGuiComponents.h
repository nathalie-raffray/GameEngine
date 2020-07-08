#pragma once
#include "Entity.h"
#include "Prefab.h"

#include "imgui.h"
#include "imgui-SFML.h"

#include "ImguiWindows.h"

/*this header can only be included once in entire solution. It is included only in ImguiWindows.cpp.
This is in accordance with ODR (One Definition Rule)

There can be more than one definition in a program of each of the following: class type, enumeration type, inline function, 
inline variable (since C++17), templated entity (template or member of template, but NOT full template specialization)...

To Avoid:
fatal error LNK1169: one or more multiply defined symbols found of ImGuiComponent<AnimationComponent>, ImGuiComponent<SpriteComponent>, etc.
*/

#define IMGUI_COMPONENT(component) if (current_prefab && *current_entity)\
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

template<class T>
void ImGuiComponent(EntityHandle eh) {};

template<>
void ImGuiComponent<AnimationComponent>(EntityHandle eh)
{
	static std::string currentAnimation = eh->get<AnimationComponent>()->currentAnimation;
	static AnimationCollection* currentAnimationCollection = Game::assets->get<AnimationCollection>(eh->get<AnimationComponent>()->animation_collection_id);
	static auto animationNames = Game::imguiWin->imgui_animation.associatedAnimations[eh->get<AnimationComponent>()->animation_collection_id];

	static bool changeAnimation = false;

	//Choose File
	static int k = 0;
	static int i = 0;
	if (ImGui::Combo("file", &k, Game::imguiWin->imgui_animation.filePaths.data(), static_cast<int>(Game::imguiWin->imgui_animation.filePaths.size())))
	{
		std::string& newAnimationCollectionID = Game::imguiWin->imgui_animation.filePathIds[Game::imguiWin->imgui_animation.filePaths[k]];
		eh->get<AnimationComponent>()->animation_collection_id = newAnimationCollectionID;
		animationNames = Game::imguiWin->imgui_animation.associatedAnimations[newAnimationCollectionID];
		currentAnimationCollection = Game::assets->get<AnimationCollection>(newAnimationCollectionID);
		i = 0;
		changeAnimation = true;
	}

	if (ImGui::Combo("animation", &i, animationNames.data(), static_cast<int>(animationNames.size())) || changeAnimation)
	{
		changeAnimation = false;

		eh->get<AnimationComponent>()->currentFrame = 0;

		currentAnimation = animationNames[i];
		eh->get<AnimationComponent>()->currentAnimation = currentAnimation;
	}
};

template<>
void ImGuiComponent<SpriteComponent>(EntityHandle eh)
{
	static int i = 0; //to choose files
	static int j = 0; //to choose sprites

	if (ImGui::Combo("filepaths", &i, Game::imguiWin->imgui_sprite.filePaths.data(), static_cast<int>(Game::imguiWin->imgui_sprite.filePaths.size())))
	{
		j = 0;
	}

	if (ImGui::Combo("sprite", &j, Game::imguiWin->imgui_sprite.sprites[Game::imguiWin->imgui_sprite.filePaths[i]].data(), static_cast<int>(Game::imguiWin->imgui_sprite.sprites[Game::imguiWin->imgui_sprite.filePaths[i]].size())))
	{
		eh->get<SpriteComponent>()->spriteId = Game::imguiWin->imgui_sprite.sprites[Game::imguiWin->imgui_sprite.filePaths[i]][j];
	}

};

template<>
void ImGuiComponent<TransformComponent>(EntityHandle eh)
{
	ImGui::InputInt2("position", &eh->get<TransformComponent>()->pos.x);
	ImGui::InputFloat("rotation z", &eh->get<TransformComponent>()->rotationz);
};

template<>
void ImGuiComponent<RenderComponent>(EntityHandle eh)
{
	static int layer;
	if (ImGui::InputInt("layer", &layer))
	{
		if (layer < 0)
		{
			layer = 0;
		}
		eh->get<RenderComponent>()->layer = static_cast<unsigned int>(layer);
	}
};

/*
template<>
void ImGuiComponent<CameraComponent>(EntityHandle eh)
{
};
*/