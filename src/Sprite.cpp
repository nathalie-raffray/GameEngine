#include "Sprite.h"
#include "AssetStorage.h"
#include "Game.h"

void to_json(json& j, const Sprite& p)
{
	j["texRect"] = p.texRect;
	//to_json(j["texRect"], p.texRect);
	j["texId"] = p.texId;
	j["scale"] = p.scale;
}

void from_json(const json& j, Sprite& p)
{
	//from_json(j["texRect"], p.texRect);
	p.texRect = j["texRect"];
	j.at("texId").get_to(p.texId);

	//set all parameters for sf::sprite
	p.m_sprite.setTextureRect(p.texRect);
	p.m_sprite.setTexture(*Game::assets->getTexture(p.texId));
	float scale = j["scale"].get<float>();
	p.m_sprite.setScale(scale, scale);
	p.scale = scale;
	try
	{
		p.m_sprite.setPosition(j.at("screenOffset").at(0).get<float>(), j.at("screenOffset").at(1).get<float>());
	}
	catch (json::out_of_range)
	{
		p.m_sprite.setPosition(0, 0);
	}
}



