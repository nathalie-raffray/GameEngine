#pragma once

/* COMPONENTS */
#include "ColliderComponent.h"
#include "AnimationComponent.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "CameraComponent.h"
#include "PlayerComponent.h"
#include "RenderComponent.h"

/* TENTITY */
#include "TEntity.h"

using Entity = TEntity<AnimationComponent, SpriteComponent, ColliderComponent, TransformComponent, CameraComponent,
	PlayerComponent, RenderComponent>;

/* ENTITY REGISTRY */
#include "EntityRegistry.h"

/* COMPONENT FACTORY */
#define ADD_COMPONENT_TO_MAP(component) component_map.emplace(#component, [](EntityHandle eh) {eh->add<component>(); })

#include <unordered_map>
struct ComponentFactory
{
	static inline std::unordered_map<std::string, void(*)(EntityHandle)> component_map;

	static void init()
	{
		ADD_COMPONENT_TO_MAP(AnimationComponent);
		ADD_COMPONENT_TO_MAP(SpriteComponent);
		ADD_COMPONENT_TO_MAP(ColliderComponent);
		ADD_COMPONENT_TO_MAP(TransformComponent);
		ADD_COMPONENT_TO_MAP(CameraComponent);
		ADD_COMPONENT_TO_MAP(PlayerComponent);
		ADD_COMPONENT_TO_MAP(RenderComponent);

	}
};

