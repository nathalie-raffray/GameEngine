#include "Camera.h"

#include "AnimationCollection.h"
#include "Game.h"
#include "AssetStorage.h"
#include "Level.h"

#include <iostream>

bool Camera::isValid(EntityHandle eh) const
{
	return ((eh->has<SpriteComponent>() || eh->has<AnimationComponent>()) && eh->has<TransformComponent>());
}

void Camera::init(EntityHandle eh)
{
	if (eh->has<PlayerComponent>())
	{
		player = eh;
	}
}

void Camera::update(float)
{
	//static_assert(player and camera is not INVALID)
	auto camera_component = Game::current_level->camera->get<CameraComponent>();
	const Vector2<int> aspectRatio = static_cast<Vector2<int>>(camera_component->aspectRatio);
	
	auto animation_component = player->get<AnimationComponent>();
	const auto& sprite = Game::assets->get<AnimationCollection>(animation_component->animation_collection_id)->getAnimation(animation_component->currentAnimation)->frames[animation_component->currentFrame].sprite.m_sprite;
	const Vector2<int> playerBounds = static_cast<Vector2<int>>(sprite.getGlobalBounds().getSize());

	Vector2<int>& playerPos = player->get<TransformComponent>()->new_pos;

	const Vector2<int> displacement = (playerPos + playerBounds / 2) - aspectRatio / 2;

	const Vector2<int> newScreenCoord0 = camera_component->screenCoord0 - displacement;
	const Vector2<int> newScreenCoord1 = camera_component->screenCoord1 - displacement;

	if ((newScreenCoord0.x < 0)
		&& !(newScreenCoord1.x - (playerPos.x + playerBounds.x / 2) < aspectRatio.x / 2))
	{
		camera_component->screenCoord0.x = newScreenCoord0.x;
		camera_component->screenCoord1.x = newScreenCoord1.x;

		for (auto e : m_entities)
		{
			auto transform = e->get<TransformComponent>();
			transform->new_pos.x -= displacement.x;
		}
	}
	//player must stay within the x bounds of the camera
	else if(playerPos.x < camera_component->screenCoord0.x)
	{
		playerPos.x = camera_component->screenCoord0.x;
	}
	else if (playerPos.x + playerBounds.x > camera_component->screenCoord1.x)
	{
		playerPos.x = camera_component->screenCoord1.x - playerBounds.x;
	}


	if ((newScreenCoord0.y < 0)
		&& !(newScreenCoord1.y - (playerPos.y + playerBounds.y / 2) < aspectRatio.y / 2))
	{
		camera_component->screenCoord0.y = newScreenCoord0.y;
		camera_component->screenCoord1.y = newScreenCoord1.y;

		for (auto e : m_entities)
		{
			auto transform = e->get<TransformComponent>();
			transform->new_pos.y -= displacement.y;
		}

	}
	//player must stay within the y bounds of the camera
	else if (playerPos.y < camera_component->screenCoord0.y)
	{
		playerPos.y = camera_component->screenCoord0.y;
	}
	else if (playerPos.y + playerBounds.y > camera_component->screenCoord1.y)
	{
		playerPos.y = camera_component->screenCoord1.y - playerBounds.y;
	}

	for (auto e : m_entities)
	{
		auto transform = e->get<TransformComponent>();
		//now collision detection and resolution on newpos has been performed in previous iteration, so just had to adjust to fit the camera, and can now update all positions. 
		transform->pos = transform->new_pos;
	}

}

