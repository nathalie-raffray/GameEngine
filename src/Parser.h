#pragma once

#include "imgui.h"
#include "imgui-SFML.h"
#include "json.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <list>
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "ResourceManager.h"
#include "SpriteComponent.h"
#include "ImguiWindows.h"

using json = nlohmann::json;

typedef sf::IntRect IntRect;
typedef sf::Sprite Sprite;
template <typename T>
using Vector2 = sf::Vector2<T>; //Vector<2> is equivalent to sf::Vector2<T>

typedef sf::Texture Texture;

//extern CAnimatedSprite sprite;
extern std::vector<CAnimatedSprite*>sprites;

extern ImguiWindows imguiWindows;

class Parser
{
private:

public:
	//think of it in terms of ownership. who owns filepath? if you want to give ownership to the function, pass by value or rvalue
	void parseSpriteFile(std::string filePath);
	void parseSpriteFile(std::string *filePath); //if filePath can be null
	void parseSpriteFile(std::string const * filePath);
	void parseSpriteFile(std::string * const filePath);
	void parseSpriteFile(std::string const * const filePath); //dont use this one and the two above
	void parseSpriteFile(std::string& filePath);
	void parseSpriteFile(std::string filePath); //cant be null, but its a rvalue. now initial string passed will be gutted. very rarely passed. when you know


	void parseSpriteFile(std::string filePath);

	void parseSpriteFile(const std::string& filePath)
	{
		std::ifstream i(filePath);
		i >> imguiWindows.jSprites;

		for (json& j : imguiWindows.jSprites)
		{

		}
		
		//iterate array of sprites
		for (json::iterator it = (imguiWindows.jSprites).begin(); it != (imguiWindows.jSprites).end(); ++it) {
			//std::cout << *it << '\n';
			//json curr = *it;
			//currSprite = sprites.emplace_back(new CAnimatedSprite);
			//currSprite->parseSprite(*it);
			
			//when a system owns an object it will use unique pointer
			//like in your animation system

			std::unique_ptr<CAnimatedSprite> upCurrentSprite;
			std::make_

			CAnimatedSprite* currSprite = new CAnimatedSprite;
			currSprite->parseSprite(*it);
			as.add(currSprite);
			
			
		}
		imguiWindows.animationInit();
	}
	void parseTextureFile(std::string filePath);

	
};