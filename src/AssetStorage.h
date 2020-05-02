#pragma once
#include "json.hpp"

#include <SFML/Graphics/Texture.hpp>

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
	friend class ImguiWindows;

	enum LoadType
	{
		TEXTURES,
		SPRITES,
		ANIMATIONS
	};

	void addAnimation(AnimationId id, std::unique_ptr<Animation> upA);
	void addAnimation(AnimationId id);
	void removeAnimation(const AnimationId& id);

	void addSprite(SpriteId id, std::unique_ptr<Sprite> upA);
	void removeSprite(const SpriteId& id);

	Animation* getAnimation(const AnimationId& id);
	Sprite* getSprite(const SpriteId& id);
	Texture* getTexture(const TextureId& id);

	void load(const std::string& filePath, const LoadType& type);

	void loadAnimations(json& js);
	void loadSprites(json& js);
	void loadTextures(json& js);

};
