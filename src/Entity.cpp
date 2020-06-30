#include "Entity.h"

#include "Game.h"
#include "AssetStorage.h"
#include "Prefab.h"

/* TO AND FROM JSON MACROS FOR ENTITY */
#include "jsonEntity.h"

void to_json(json& j, const Entity& entity)
{
	TOJSON(PrefabComponent);
	TOJSON(AnimationComponent);
	TOJSON(TransformComponent);
	TOJSON(RenderComponent);
	TOJSON(PlayerComponent);
	TOJSON(CameraComponent);



	/*if (entity.has<AssetComponent>())
	{
		j["AssetComponent"] = *entity.get<AssetComponent>();
	}
	if (entity.has<AnimationComponent>())
	{
		j["AnimationComponent"] = *entity.get<AnimationComponent>();
	}*/
}

void from_json(const json& j, Entity& entity)
{
	FROMJSON_PREFABCOMPONENT();
	FROMJSON(AnimationComponent);
	FROMJSON(TransformComponent);
	FROMJSON(RenderComponent);
	FROMJSON(PlayerComponent);
	FROMJSON(CameraComponent);



	/*if (has_field<std::string>(j, "AssetComponent"))
	{
		EntityAsset* prefab = Game::assets->get<EntityAsset>(j["AssetComponent"]["entity_asset_id"]);
		entity.clone(*prefab->entity_immutable);
		entity.add<AssetComponent>();
		PARSE(*entity.get<AssetComponent>() = j["AssetComponent"]);
	}
	if (has_field<std::string>(j, "AnimationComponent"))
	{
		entity.add<AnimationComponent>();
		PARSE(*entity.get<AnimationComponent>() = j["AnimationComponent"]);
	}

	for (auto& jj : j.items())
	{
		if (jj.key() == "AssetComponent")
		{
			EntityAsset* prefab = Game::assets->get<EntityAsset>(jj.value()["entity_asset_id"]);
			entity.clone(*prefab->entity_immutable);
			entity.add<AssetComponent>();
			*entity.get<AssetComponent>() = jj.value();
		}
		else
		{
			if (jj.key() == "AnimationComponent")
			{
				entity.add<AnimationComponent>();
				*entity.get<AnimationComponent>() = jj.value();
			}
			if (jj.key() == "SpriteComponent")
			{
				entity.add<SpriteComponent>();
				*entity.get<SpriteComponent>() = jj.value();
			}
			if (jj.key() == "AnimationComponent")
			{
				entity.add<AnimationComponent>();
				*entity.get<AnimationComponent>() = jj.value();
			}
			if (jj.key() == "AnimationComponent")
			{
				entity.add<AnimationComponent>();
				*entity.get<AnimationComponent>() = jj.value();
			}
			if (jj.key() == "AnimationComponent")
			{
				entity.add<AnimationComponent>();
				*entity.get<AnimationComponent>() = jj.value();
			}
		}
	}*/
}