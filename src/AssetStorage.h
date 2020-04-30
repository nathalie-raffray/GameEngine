#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <unordered_map>
#include <memory>
#include <fstream>
#include "Texture.h"
#include "Sprite.h"
#include "SpriteComponent.h"
#include "AnimationComponent.h"
#include "Animation.h"
#include "AnimationCollection.h"
#include "AnimationFrame.h"
#include "Game.h"
#include "json.hpp"


using json = nlohmann::json;

using SpriteId = std::string;
using TextureId = std::string;
using AnimationId = std::string;
//using AnimationCollectionId = std::string;

using IntRect = sf::IntRect;
using Texture = sf::Texture;
//struct Texture;
struct Sprite;
struct Animation;
//struct AnimationCollection;

using TextureMap				 = std::unordered_map<TextureId, std::unique_ptr<Texture>>;
using SpriteMap					 = std::unordered_map<SpriteId, std::unique_ptr<Sprite>>;
using AnimationMap				 = std::unordered_map<AnimationId, std::unique_ptr<Animation>>;
//using AnimationCollectionMap	 = std::unordered_map<AnimationCollectionId, std::unique_ptr<AnimationCollection>>;
//using AnimationCollectionMap = std::unordered_map<AnimationCollectionId, std::vector<AnimationId>>;

class AssetStorage
{
private:

	TextureMap textures;
	SpriteMap sprites;
	AnimationMap animations;
	//AnimationCollectionMap animation_collections;

public:

	enum LoadType
	{
		TEXTURES,
		SPRITES,
		ANIMATIONS
	};

	void addAnimation(AnimationId id, std::unique_ptr<Animation>&& upA)
	{
		animations.emplace(id, std::move(upA));
	}

	void addSprite(SpriteId id, std::unique_ptr<Sprite>&& upA)
	{
		sprites.emplace(id, std::move(upA));
	}

	Animation* getAnimation(const AnimationId& id) { return animations[id].get(); }

	Sprite* getSprite(const SpriteId& id) { return sprites[id].get(); }

	Texture* getTexture(const TextureId& id) { return textures[id].get(); }

	void load(const std::string& filePath, const LoadType& type)
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
			break;
		}
	}

	void loadAnimations(json& js)
	{
		for (json& j : js["animations"])
		{
			auto uA = std::make_unique<Animation>();
			
			loadSprites(j["sprites"]);	
			
			*uA = j;

			//addAnimation(j["animationId"].get<std::string>(), std::move(uA));
			animations.emplace(j["animationId"].get<std::string>(), std::move(uA));
		}
	}

	void loadSprites(json& js)
	{
		for (json& j : js["sprites"])
		{
			auto uS = std::make_unique<Sprite>();

			*uS = j;

			//addSprite(js["spriteId"].get<std::string>(), std::move(uS));
			sprites.emplace(js["spriteId"].get<std::string>(), std::move(uS));

		}
	}

	void loadTextures(json& js)
	{
		for (json& j : js["textures"])
		{
			auto uT = std::make_unique<Texture>();
			assert(uT->loadFromFile(j["filepath"].get<std::string>()));
			textures.emplace(j["texId"].get<std::string>(), std::move(uT));
		}
	}


	/*static Sprite get(SpriteId spriteId);*/
};





/*

void to_json(json& j, const AnimationComponent& p)
{

}

void from_json(const json& j, AnimationComponent& p)
{

}
*/