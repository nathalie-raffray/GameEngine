#pragma once
/* COMPONENTS */
#include "ColliderComponent.h"
#include "AnimationComponent.h"
#include "SpriteComponent.h"

/* TENTITY */
#include "TEntity.h"

using Entity = TEntity<AnimationComponent, SpriteComponent, ColliderComponent>;

