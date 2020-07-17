#include "Sprite.h"
#include "AssetStorage.h"
#include "Texture.h"
#include "Entity.h"
#include "AnimationCollection.h"
#include "jsonSFML.h"
#include <fstream>

//----------------------------------------------------------------------------------------------

void to_json(json& j, const Sprite& p)
{
	j["texRect"] = p.texRect;
	j["texId"] = p.texId;
	//j["scale"] = p.scale;
}

//----------------------------------------------------------------------------------------------

void from_json(const json& j, Sprite& p)
{
	p.texRect = j["texRect"];
	j.at("texId").get_to(p.texId);

	//set all parameters for sf::sprite
	p.m_sprite.setTextureRect(p.texRect);
	p.m_sprite.setTexture(Game::assets->get<Texture>(p.texId)->texture);
	//float scale = j["scale"].get<float>();
	//p.m_sprite.setScale(scale, scale);
	//p.scale = scale;
	try
	{
		p.m_sprite.setPosition(j.at("screenOffset").at(0).get<float>(), j.at("screenOffset").at(1).get<float>());
	}
	catch (json::out_of_range)
	{
		p.m_sprite.setPosition(0, 0);
	}
}

//----------------------------------------------------------------------------------------------

sf::FloatRect Sprite::getBounds(EntityHandle eh)
{
	ASSERT(eh->has<AnimationComponent>() || eh->has<SpriteComponent>());
	
	if (eh->has<AnimationComponent>())
	{
		Animation* animation1 = Game::assets->get<AnimationCollection>(eh->get<AnimationComponent>()->animation_collection_id)->getAnimation(eh->get<AnimationComponent>()->currentAnimation);
		auto sprite1 = animation1->frames[eh->get<AnimationComponent>()->currentFrame].sprite.m_sprite;
		return sprite1.getGlobalBounds();
	}
	
	if (eh->has<SpriteComponent>())
	{
		return Game::assets->get<Sprite>(eh->get<SpriteComponent>()->spriteId)->m_sprite.getGlobalBounds();
	}
	return {}; //?
}

//----------------------------------------------------------------------------------------------

bool Sprite::load(const std::string& filePath)
{
	json js;
	std::ifstream i(filePath);
	i >> js;

	for (json& j : js["sprites"])
	{
		auto uS = std::make_unique<Sprite>();

		*uS = j;

		Game::assets->assets.emplace(j["spriteId"].get<std::string>(), std::move(uS));
	}
	
	return true;
}
