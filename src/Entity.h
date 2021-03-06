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
#include "RigidBodyComponent.h"
#include "HealthComponent.h"
#include "HitboxComponent.h"


/* TENTITY */
#include "TEntity.h"

using Entity = TEntity<AnimationComponent, SpriteComponent, ColliderComponent, TransformComponent, CameraComponent,
	PlayerComponent, RenderComponent, PrefabComponent, RigidBodyComponent, HealthComponent, HitboxComponent>;

/* ENTITY REGISTRY */
#include "EntityRegistry.h"

/* JSON */
void to_json(json& j, const Entity& entity);
void from_json(const json& j, Entity& entity);


