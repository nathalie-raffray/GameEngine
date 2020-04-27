#pragma once
#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <iostream>
#include <unordered_map>


typedef sf::IntRect IntRect;
typedef sf::Sprite Sprite;
template <typename T>
using Vector2 = sf::Vector2<T>; //Vector<2> is equivalent to sf::Vector2<T>

typedef sf::Texture Texture;


//this is where I keep track of all loaded textures, maybe make this a singleton (it will at least act like one)
//map of textures map<std::string, Texture*> 

class ResourceManager
{
private:
	typedef std::unordered_map<std::string, Texture*> TextureMap;
	TextureMap m_texMap;
public:

	void addTexture(std::string name, std::string filepath)
	{
		Texture* tex = new Texture;
		assert(tex->loadFromFile(filepath));
		m_texMap[name] = tex;
	}

	Texture* getTexture(std::string name)
	{
		return m_texMap[name];
	}

	void removeTexture(const std::string& name)
	{
		delete m_texMap[name];
		m_texMap.erase(name);
	}

	~ResourceManager()
	{
		for (auto& val : m_texMap) delete val.second;
		m_texMap.clear();
	}
};