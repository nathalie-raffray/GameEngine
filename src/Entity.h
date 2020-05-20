#pragma once
#include "ColliderComponent.h"
#include "AnimationComponent.h"
#include "SpriteComponent.h"
#include "TEntity.h"

using Entity = TEntity<AnimationComponent, SpriteComponent, ColliderComponent>;
