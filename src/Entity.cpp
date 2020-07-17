#include "Entity.h"

/* TO AND FROM JSON MACROS FOR ENTITY */
#include "jsonEntity.h"

void to_json(json& j, const Entity& entity)
{
	TOJSON(PrefabComponent);
	TOJSON(AnimationComponent);
	TOJSON(SpriteComponent);
	TOJSON(TransformComponent);
	TOJSON(RenderComponent);
	TOJSON(PlayerComponent);
	TOJSON(CameraComponent);
	TOJSON(RigidBodyComponent);
	TOJSON(ColliderComponent);

}

void from_json(const json& j, Entity& entity)
{
	FROMJSON_PREFABCOMPONENT();
	FROMJSON(AnimationComponent);
	FROMJSON(SpriteComponent);
	FROMJSON(TransformComponent);
	FROMJSON(RenderComponent);
	FROMJSON(PlayerComponent);
	FROMJSON(CameraComponent);
	FROMJSON(RigidBodyComponent);
	FROMJSON(ColliderComponent);

}