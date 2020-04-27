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
	void parseSpriteFile(std::string filePath)
	{
		std::ifstream i(filePath);
		i >> imguiWindows.jSprites;

		CAnimatedSprite* currSprite;
		//iterate array of sprites
		for (json::iterator it = (imguiWindows.jSprites).begin(); it != (imguiWindows.jSprites).end(); ++it) {
			//std::cout << *it << '\n';
			//json curr = *it;
			//currSprite = sprites.emplace_back(new CAnimatedSprite);
			//currSprite->parseSprite(*it);
			currSprite = new CAnimatedSprite;
			currSprite->parseSprite(*it);
			as.add(currSprite);
			
			
		}
		imguiWindows.animationInit();
	}
	void parseTextureFile(std::string filePath);

	
};