
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

#include "ResourceManager.h"
#include "SpriteComponent.h"

typedef sf::IntRect IntRect;
typedef sf::Clock Clock;
typedef sf::Sprite Sprite;
template <typename T>
using Vector2 = sf::Vector2<T>; //Vector<2> is equivalent to sf::Vector2<T>

typedef sf::Texture Texture;

class AnimationSystem
{
private:
	//list of entities eventually
	CAnimatedSprite* spriteComponent;
	std::vector<CAnimatedSprite*> sprites;
	
	Clock clock; //int64
public:
	friend class ImguiWindows;

	AnimationSystem(CAnimatedSprite* sc) : spriteComponent(sc) {}
	AnimationSystem() {}
	~AnimationSystem();

	void add(CAnimatedSprite* sc);
	void remove(CAnimatedSprite* sc);

	void playAnimation(std::string name);
	void pauseAnimation();

	void update();
	void draw(sf::RenderWindow& window) { for (CAnimatedSprite* sprite : sprites) if(sprite->isEnabled()) window.draw(sprite->m_sprite);  }

	inline void updateTextureRect(CAnimatedSprite* sc);
	inline void updatePositionOffset(CAnimatedSprite* sc);
	inline void updateScale(CAnimatedSprite* sc);
	inline void updateRotation(CAnimatedSprite* sc, float angle);

	void imguiAnimationEditor();

};

