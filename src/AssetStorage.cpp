#include "AssetStorage.h"

#include <string>
#include <unordered_map>
#include <fstream>
#include <memory>

#include "Sprite.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "Animation.h"
#include "AnimationCollection.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "ImguiWindows.h"

//----------------------------------------------------------------------------------------------
/*
void AssetStorage::addAnimation(AnimationId id, std::unique_ptr<Animation> upA)
{
	animations.emplace(id, std::move(upA));
}
*/

//----------------------------------------------------------------------------------------------
/*
void AssetStorage::addAnimation(AnimationId id)
{
	animations.emplace(id, std::make_unique<Animation>());
}
*/

//----------------------------------------------------------------------------------------------

/*
void AssetStorage::removeAnimation(const AnimationId& id)
{
	animations.erase(id);
}
*/

//----------------------------------------------------------------------------------------------

void AssetStorage::addSprite(SpriteId id, std::unique_ptr<Sprite> upA)
{
	sprites.emplace(id, std::move(upA));
}

//----------------------------------------------------------------------------------------------

void AssetStorage::removeSprite(const SpriteId& id)
{
	sprites.erase(id);
}

//----------------------------------------------------------------------------------------------
/*
Animation* AssetStorage::getAnimation(const AnimationId& id)
{
	if (animations.count(id) == 0) return nullptr;
	else return animations[id].get();
}
*/

//----------------------------------------------------------------------------------------------

AnimationCollection* AssetStorage::getAnimationCollection(const AnimationCollectionId& id)
{
	if (animation_collections.count(id) == 0) return nullptr;
	else return animation_collections[id].get();
}

//----------------------------------------------------------------------------------------------

Sprite* AssetStorage::getSprite(const SpriteId& id)
{
	if (sprites.count(id) == 0) return nullptr;
	else return sprites[id].get();
}

//----------------------------------------------------------------------------------------------

Texture* AssetStorage::getTexture(const TextureId& id)
{
	if (textures.count(id) == 0) return nullptr;
	else return textures[id].get();
}

//----------------------------------------------------------------------------------------------

void AssetStorage::load(const std::string& filePath, const LoadType& type)
{
	json js;
	std::ifstream i(filePath);
	i >> js;

	switch (type) {
	case TEXTURES:
		loadTextures(js);
		break;
	case SPRITES:
		loadSprites(js);
		break;
	case ANIMATIONS:
		loadAnimations(js);
		//Game::imguiWin->addJson(filePath);
		break;
	}
}

//----------------------------------------------------------------------------------------------

void AssetStorage::loadAnimations(json& js)
{
	auto uAC = std::make_unique<AnimationCollection>();
	
	for (json& j : js["animations"])
	{
		auto uA = std::make_unique<Animation>();

		loadSprites(j["sprites"]);

		*uA = j;

		uAC->animations.emplace(j["animationId"].get<std::string>(), std::move(uA));

		//Game::imguiWin->addAssociatedAnimation(filePath, animations.find(j["animationId"].get<std::string>())->first); //only necessary for ImGui animation editor
	}

	animation_collections.emplace(js["name"], std::move(uAC));
}

//----------------------------------------------------------------------------------------------

void AssetStorage::loadSprites(json& js)
{
	for (json& j : js)
	{
		auto uS = std::make_unique<Sprite>();

		*uS = j;

		sprites.emplace(j["spriteId"].get<std::string>(), std::move(uS));

	}
}

//----------------------------------------------------------------------------------------------

void AssetStorage::loadTextures(json& js)
{
	for (json& j : js["textures"])
	{
		auto uT = std::make_unique<Texture>();
		assert(uT->loadFromFile(j["filepath"].get<std::string>()));
		textures.emplace(j["texId"].get<std::string>(), std::move(uT));
	}
}

//----------------------------------------------------------------------------------------------
