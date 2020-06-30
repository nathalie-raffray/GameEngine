#pragma once
#include "Entity.h"
#include "Prefab.h"

#include "imgui.h"
#include "imgui-SFML.h"

template<class T>
void ImGui(EntityHandle eh) {};

template<>
void ImGui<AnimationComponent>(EntityHandle eh)
{
	/*if (eh->has<AnimationComponent>())
	{
		//static const char* name = "animation component"; //?
		if (ImGui::TreeNode(AnimationComponent::name))
		{
		}
	}*/

	static char animationCollectionId[50];
	if (ImGui::InputText("animation collection id", animationCollectionId, 50))
	{
		eh->get<AnimationComponent>()->animation_collection_id = animationCollectionId;
	}
	static char animationId[50];
	if (ImGui::InputText("first animation id", animationId, 50))
	{
		eh->get<AnimationComponent>()->currentAnimation = animationId;
	}
};

template<>
void ImGui<SpriteComponent>(EntityHandle eh)
{
	static const char* name = "sprite component"; //?
	if (ImGui::TreeNode(name))
	{
		static char spriteId[50];
		if (ImGui::InputText("sprite id", spriteId, 50))
		{

		}
	}
};

template<>
void ImGui<TransformComponent>(EntityHandle eh)
{
	static const char* name = "transform component"; //?
	if (ImGui::TreeNode(name))
	{
		ImGui::InputInt2("position", &eh->get<TransformComponent>()->pos.x);
		ImGui::InputFloat("rotation z", &eh->get<TransformComponent>()->rotationz);
	}
};