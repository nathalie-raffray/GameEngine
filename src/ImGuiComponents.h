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
	if (!current_prefab->entity_immutable.has<component>() && current_entity->has<component>())\
	{\
		if (ImGui::TreeNode(component::name))\
		{\
			ImGuiComponent<component>(current_entity, init_component_imgui);\
			ImGui::TreePop();\
		}\
	}\
}

template<class T>
void ImGuiComponent(EntityHandle eh, bool init = false) {};

//----------------------------------------------------------------------------------------------

template<>
void ImGuiComponent<AnimationComponent>(EntityHandle eh, bool init)
{
	static std::string currentAnimation = eh->get<AnimationComponent>()->currentAnimation;
	static AnimationCollection* currentAnimationCollection = Game::assets->get<AnimationCollection>(eh->get<AnimationComponent>()->animation_collection_id);
	static auto animationNames = Game::imguiWin->imgui_animation.associatedAnimations[eh->get<AnimationComponent>()->animation_collection_id];

	static bool changeAnimation = false;

	static int i = 0; //choose file
	static int j = 0; //choose animation

	if (!init)
	{
		currentAnimation = eh->get<AnimationComponent>()->currentAnimation;
		currentAnimationCollection = Game::assets->get<AnimationCollection>(eh->get<AnimationComponent>()->animation_collection_id);
		animationNames = Game::imguiWin->imgui_animation.associatedAnimations[eh->get<AnimationComponent>()->animation_collection_id];

		i = 0;
		j = 0;

		auto entity_animation_filepath = Game::assets->table_of_contents[eh->get<AnimationComponent>()->animation_collection_id];

		for (auto& filepath : Game::imguiWin->imgui_animation.filePaths)
		{
			if (std::string(filepath) == entity_animation_filepath)
			{
				break;
			}
			i++;
		}
		ASSERT(i < static_cast<int>(Game::imguiWin->imgui_animation.filePaths.size()));

		for (auto& animation : animationNames)
		{
			if (std::string(animation) == currentAnimation)
			{
				break;
			}
			j++;
		}
		ASSERT(j < static_cast<int>(animationNames.size()));

	}

	if (ImGui::Combo("file", &i, Game::imguiWin->imgui_animation.filePaths.data(), static_cast<int>(Game::imguiWin->imgui_animation.filePaths.size())))
	{
		std::string& newAnimationCollectionID = Game::imguiWin->imgui_animation.filePathIds[Game::imguiWin->imgui_animation.filePaths[i]];
		eh->get<AnimationComponent>()->animation_collection_id = newAnimationCollectionID;
		animationNames = Game::imguiWin->imgui_animation.associatedAnimations[newAnimationCollectionID];
		currentAnimationCollection = Game::assets->get<AnimationCollection>(newAnimationCollectionID);
		j = 0;
		changeAnimation = true;
	}

	if (ImGui::Combo("animation", &j, animationNames.data(), static_cast<int>(animationNames.size())) || changeAnimation)
	{
		changeAnimation = false;

		eh->get<AnimationComponent>()->currentFrame = 0;

		currentAnimation = animationNames[j];
		eh->get<AnimationComponent>()->currentAnimation = currentAnimation;
	}
};

//----------------------------------------------------------------------------------------------

template<>
void ImGuiComponent<SpriteComponent>(EntityHandle eh, bool init)
{
	static int i = 0; //to choose files
	static int j = 0; //to choose sprites

	if (!init)
	{
		auto entity_spriteid = eh->get<SpriteComponent>()->spriteId;
		auto entity_sprite_filepath = Game::assets->table_of_contents[entity_spriteid];

		i = 0;
		j = 0;

		for (auto& filepath : Game::imguiWin->imgui_sprite.filePaths)
		{
			if (std::string(filepath) == entity_sprite_filepath)
			{
				break;
			}
			i++;
		}
		for (auto& spriteid : Game::imguiWin->imgui_sprite.sprites[Game::imguiWin->imgui_sprite.filePaths[i]])
		{
			if (std::string(spriteid) == entity_spriteid)
			{
				break;
			}
			j++;
		}
	}

	if (ImGui::Combo("filepaths", &i, Game::imguiWin->imgui_sprite.filePaths.data(), static_cast<int>(Game::imguiWin->imgui_sprite.filePaths.size())))
	{
		j = 0;
	}

	if (ImGui::Combo("sprite", &j, Game::imguiWin->imgui_sprite.sprites[Game::imguiWin->imgui_sprite.filePaths[i]].data(), static_cast<int>(Game::imguiWin->imgui_sprite.sprites[Game::imguiWin->imgui_sprite.filePaths[i]].size())))
	{
		eh->get<SpriteComponent>()->spriteId = Game::imguiWin->imgui_sprite.sprites[Game::imguiWin->imgui_sprite.filePaths[i]][j];
	}

};

//----------------------------------------------------------------------------------------------

template<>
void ImGuiComponent<TransformComponent>(EntityHandle eh, bool init)
{
	ImGui::InputFloat2("position", &eh->get<TransformComponent>()->new_pos.x);
	ImGui::InputFloat("rotation z", &eh->get<TransformComponent>()->rotationz);
	ImGui::InputFloat("scale", &eh->get<TransformComponent>()->scale);
};

//----------------------------------------------------------------------------------------------

template<>
void ImGuiComponent<RenderComponent>(EntityHandle eh, bool init)
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

//----------------------------------------------------------------------------------------------

template<>
void ImGuiComponent<RigidBodyComponent>(EntityHandle eh, bool init)
{
	ImGui::Checkbox("is kinematic", &eh->get<RigidBodyComponent>()->is_kinematic);
	ImGui::InputFloat2("velocity", &eh->get<RigidBodyComponent>()->velocity.x);
	ImGui::InputFloat("gravity", &eh->get<RigidBodyComponent>()->gravity);
};

//----------------------------------------------------------------------------------------------

template<>
void ImGuiComponent<ColliderComponent>(EntityHandle eh, bool init)
{
	bool is_trigger = eh->get<ColliderComponent>()->is_trigger;
	if (eh->has<RigidBodyComponent>())
	{
		if (eh->get<RigidBodyComponent>()->is_kinematic && is_trigger)
		{
			ImGui::Text("collider type: trigger kinematic dynamic");
		}
		else if (is_trigger)
		{
			ImGui::Text("collider type: trigger dynamic");
		}
		else
		{
			ImGui::Text("collider type: dynamic");
		}
	}
	else {
		if (is_trigger)
		{
			ImGui::Text("collider type: trigger static");
		}
		else {
			ImGui::Text("collider type: static");
		}
	}

	ImGui::Checkbox("is trigger", &eh->get<ColliderComponent>()->is_trigger);
};

//----------------------------------------------------------------------------------------------

template<>
void ImGuiComponent<PrefabComponent>(EntityHandle eh, bool init)
{
	ImGui::Text("prefab name: ");
	ImGui::Text(eh->get<PrefabComponent>()->prefab_id.c_str());
};

//----------------------------------------------------------------------------------------------

template<>
void ImGuiComponent<HealthComponent>(EntityHandle eh, bool init)
{
	auto health = eh->get<HealthComponent>();
	ImGui::InputInt("max health", &health->max_health);
	/*ImGui::InputInt("damage to other", &health->damage_to_other);
	if (eh->has<AnimationComponent>())
	{
		ImGui::Text("hit animation", &health->hit_animation);
		ImGui::Text("death animation", &health->death_animation);
	}*/
};
