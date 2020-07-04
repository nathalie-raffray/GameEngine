#include "RenderingSystem.h"

#include "AssetStorage.h"
#include "Game.h"
#include "AnimationCollection.h"
#include "Level.h"

//----------------------------------------------------------------------------------------------

bool RenderingSystem::isValid(EntityHandle h) const
{
	return ((h->has<AnimationComponent>() || h->has<SpriteComponent>()) && h->has<TransformComponent>() && h->has<RenderComponent>());
}

//----------------------------------------------------------------------------------------------

void RenderingSystem::update(float dt) 
{
	for (auto& entity : m_entities)
	{
		sf::Sprite* sprite = nullptr;

		if (entity->has<AnimationComponent>())
		{
			auto animation_component = entity->get<AnimationComponent>();
			Animation* animation = Game::assets->get<AnimationCollection>(animation_component->animation_collection_id)->getAnimation(animation_component->currentAnimation);

			if (!animation) continue;//for debug purposes

			int totalFrames = static_cast<int>(animation->frames.size());
			if (totalFrames == 0) continue; //for debug purposes

			sprite = &animation->frames[animation_component->currentFrame].sprite.m_sprite;
		}
		else if (entity->has<SpriteComponent>())
		{
			auto sprite_component = entity->get<SpriteComponent>();
			Sprite* s = Game::assets->get<Sprite>(sprite_component->spriteId);
			ASSERT(s);
			sprite = &s->m_sprite;
		}

		auto transform = entity->get<TransformComponent>();
		sprite->setPosition((float)transform->pos.x, (float)transform->pos.y);
		sprite->setRotation(transform->rotationz);
		//sprite->scale({ Game::current_level->camera->get<CameraComponent>()->zoom, Game::current_level->camera->get<CameraComponent>()->zoom });
		auto original_scale = sprite->getScale();
		sprite->scale({ Game::current_level->camera->get<CameraComponent>()->zoom, Game::current_level->camera->get<CameraComponent>()->zoom });
		Game::window->draw(*sprite);
		sprite->setScale(original_scale);
	}
}

//----------------------------------------------------------------------------------------------

void RenderingSystem::add(EntityHandle h)
{
	if (isValid(h))
	{
		//m_entities will be sorted by lowest to greatest render layer within rendering system
		//auto it = std::lower_bound(m_entities.begin(), m_entities.end(), h,
			//[](EntityHandle entity1, EntityHandle entity2) -> bool {return entity1->get<RenderComponent>()->layer <= entity2->get<RenderComponent>()->layer; });
		//if(it!=m_entities.end()) std::cout << "layer: " << it->operator->()->get<RenderComponent>()->layer << std::endl;
		std::cout << h->get<RenderComponent>()->layer << std::endl;
		m_entities.insert(std::lower_bound(m_entities.begin(), m_entities.end(), h, 
			[](EntityHandle entity1, EntityHandle entity2) -> bool {return entity1->get<RenderComponent>()->layer <= entity2->get<RenderComponent>()->layer; }), h);
		
		init(h);
	}
}

//----------------------------------------------------------------------------------------------
