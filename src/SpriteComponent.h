#pragma once
#include "imgui.h"
#include "imgui-SFML.h"
#include "json.hpp"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <iostream>
#include <unordered_map>

#include "ResourceManager.h"

using json = nlohmann::json;

typedef sf::Clock Clock;
typedef sf::IntRect IntRect;
typedef sf::Sprite Sprite;
template <typename T>
using Vector2 = sf::Vector2<T>; //Vector<2> is equivalent to sf::Vector2<T>

typedef sf::Texture Texture;


struct Animation
{
	std::vector<IntRect> m_texRects;
	std::vector<IntRect> m_screenRects;
	int m_currFrame;
	int m_numFrames;
	int m_speed; //delay in milliseconds
	bool m_loop;

	Animation()
		: m_texRects{ 0 }, m_screenRects{ 0 }, m_currFrame(0), m_numFrames(0), m_speed(0), m_loop(false) {}

	Animation(std::vector<IntRect> texRects, std::vector<IntRect> screenRects, unsigned int currFrame, unsigned int numFrames, unsigned int speed, bool loop)
		: m_texRects(texRects), m_screenRects(screenRects), m_currFrame(currFrame), m_numFrames(numFrames), m_speed(speed), m_loop(loop) {}


	inline IntRect& getCurrTexRect() { return m_texRects[m_currFrame]; }

	inline float getCurrScreenOffsetX() { return m_screenRects[m_currFrame].left;  }
	inline float getCurrScreenOffsetY() { return m_screenRects[m_currFrame].top; }

	inline float getCurrScaleX() { return static_cast<float>(m_screenRects[m_currFrame].width) / m_texRects[m_currFrame].width; }
	inline float getCurrScaleY() { return static_cast<float>(m_screenRects[m_currFrame].height) / m_texRects[m_currFrame].height; }

	inline Vector2<float> getCurrScreenOffset() { //fix this, there will be too much copying
		return Vector2<float>(m_screenRects[m_currFrame].left, m_screenRects[m_currFrame].top);
	}
	inline Vector2<float> getCurrScale() {
		return Vector2<float>(static_cast<float>(m_screenRects[m_currFrame].width) / m_texRects[m_currFrame].width,
							 static_cast<float>(m_screenRects[m_currFrame].height) / m_texRects[m_currFrame].height);
	}
};

class CAnimatedSprite
{
private:	
	std::string m_spriteName;
	std::string m_texName;
	Texture* m_tex;
	bool m_enabled;
	bool animationPaused = false;

	typedef std::unordered_map<std::string, Animation> AnimationMap;
	//need to make animation a pointer to the heap
	AnimationMap animations;


public:
	friend class ImguiWindows;

	Sprite m_sprite;
	Animation* animPlaying;
	//a separate component for unanimated sprites would have no clock data or Animation data
	Clock internalClock; //int64

	CAnimatedSprite();
	CAnimatedSprite(std::string_view sn);

	void init();

	const std::string& getName() { return m_spriteName; }

	Animation* getAnimation(std::string animName);
	void addAnimation(std::string animName);
	void addAnimation(std::string animName, std::vector<IntRect> texRects, std::vector<IntRect> screenRects, unsigned int numFrames, unsigned int speed, bool loop);
	void removeAnimation(std::string animName);

	void setTexture(std::string texName);

	inline bool isEnabled() { return m_enabled; }
	void enable() { m_enabled = true; }
	void disable() { m_enabled = false; }
	bool isPaused() { return animationPaused; }
	void pauseAnimation() { animationPaused = true; }
	void playAnimation() { animationPaused = false; }

	void parseSprite(json info)
	{
		m_spriteName = info["spriteName"];
		m_texName = info["texName"];
		setTexture(m_texName);

		m_enabled = info["enabled"];

		json anim, currTexRect, currScreenRect;

		//iterate array of animations
		for (json::iterator it = info["animations"].begin(); it != info["animations"].end(); ++it) {
			//std::cout << *it << '\n';
			anim = *it;
			
			std::vector<IntRect> texRect, screenRect;
			//std::cout << anim["numFrames"];
			for (int i = 0; i < anim["numFrames"]; i++)
			{
				currTexRect = anim["texRect"][i];
				currScreenRect = anim["screenRect"][i];
				texRect.emplace_back(currTexRect[0], currTexRect[1], currTexRect[2], currTexRect[3]);
				screenRect.emplace_back(currScreenRect[0], currScreenRect[1], currScreenRect[2], currScreenRect[3]);
			}
			
			animations.insert({ anim["animName"],
							Animation(texRect, screenRect, 0, anim["numFrames"], anim["speed"], anim["loop"]) });

		}
	}


	/*inline void setTextureRect(std::string animName);
	//inline void setTextureRect();
	inline void setLocalTextureRect(std::string animName, int frameIndex, IntRect& ir);

	inline void setPosition(Vector2<float>& pos);
	inline void setPosition(float px, float py);

	inline void setScale(Vector2<float>& sc);
	inline void setScale(float sx, float sy);

	inline void setRotation(float angle);*/
};