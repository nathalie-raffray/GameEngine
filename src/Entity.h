#pragma once

/* COMPONENTS */
#include "ColliderComponent.h"
#include "AnimationComponent.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "PlayerComponent.h"
#include "RenderComponent.h"
#include "PrefabComponent.h"

/* TENTITY */
#include "TEntity.h"

using Entity = TEntity<AnimationComponent, SpriteComponent, ColliderComponent, TransformComponent, CameraComponent,
	PlayerComponent, RenderComponent, PrefabComponent>;

/* ENTITY REGISTRY */
#include "EntityRegistry.h"

/* JSON */
void to_json(json& j, const Entity& entity);
void from_json(const json& j, Entity& entity);

//#include "ImGuiComponents.h"
/* COMPONENT FACTORY */
/*#define ADD_COMPONENT_TO_MAP(component) add_component_map.emplace(#component, [](EntityHandle eh) {if(!eh->has<component>) eh->add<component>(); }); \
										json_component_map.emplace(#component, [](json& j, EntityHandle eh) {*eh->get<component>() = j; }); \
										imgui_component_map.emplace(#component, [](EntityAsset ea) { \
											static bool programmable;\
										}) */

/*if (ImGui::Checkbox("programmable", &programmable))\
{\
if (programmable) {
	\
		ea->entity_immutable->remove<component>(); \
		ea->entity_programmable->add<component>(); \
}\
else\
{\
ea->entity_immutable->add<component>(); \
ea->entity_programmable->remove<component>(); \
}\
}\
if (ea->entity_immutable->has<component>()) {
	\
		if (ImGui::TreeNode(#component)) {
			\
				ImGui<component>(ea->entity_immutable); \
		}
}\
if (ea->entity_programmable->has<component>()) {
	\
		if (ImGui::TreeNode(#component)) {
			\
				ImGui<component>(ea->entity_programmable); \
		}\
}\*/

										//imgui_component_map.emplace(#component, [](EntityHandle eh) { if (eh->has<component>()){ if (ImGui::TreeNode(#component)){ ImGui<component>(eh);}  }})

//#define ADD_COMPONENT_TO_MAP(component) component_map.emplace(#component, [](EntityHandle eh) { if (eh->has<component>()){ if (ImGui::TreeNode("component")){ImGui<component>(eh);}  }})

#include <unordered_map>
struct ComponentFactory
{
	//static inline std::unordered_map<std::string, void(*)(EntityHandle)> add_component_map;
	//static inline std::unordered_map<std::string, void(*)(json & j, EntityHandle)> json_component_map;
	//static inline std::unordered_map<std::string, void(*)(EntityHandle)> imgui_component_map;
	//static inline std::unordered_map<std::string, void(*)(EntityAsset)> imgui_component_map;

	static void init()
	{
	/*	ADD_COMPONENT_TO_MAP(AnimationComponent);
		ADD_COMPONENT_TO_MAP(SpriteComponent);
		ADD_COMPONENT_TO_MAP(ColliderComponent);
		ADD_COMPONENT_TO_MAP(TransformComponent);
		ADD_COMPONENT_TO_MAP(CameraComponent);
		ADD_COMPONENT_TO_MAP(PlayerComponent);
		ADD_COMPONENT_TO_MAP(RenderComponent);*/

	}
};

