#include "SpriteComponent.h"

extern ResourceManager resManager;

//----------------------------------------------------------------------------------------------

CAnimatedSprite::CAnimatedSprite()
	: m_tex(nullptr), m_enabled(false), animPlaying(nullptr) 
{
	//init();
}

//----------------------------------------------------------------------------------------------

CAnimatedSprite::CAnimatedSprite(std::string_view sn)
	: m_spriteName(sn), m_texName(""), m_tex(nullptr), m_enabled(false), animPlaying(nullptr) 
{
	//init();
}

//----------------------------------------------------------------------------------------------

void CAnimatedSprite::init()
{
	//m_sprite.setTextureRect({ 0,0,0,0 });
}

//----------------------------------------------------------------------------------------------

Animation* CAnimatedSprite::getAnimation(std::string animName) { return &animations[animName]; }

//----------------------------------------------------------------------------------------------

void CAnimatedSprite::addAnimation(std::string animName)
{
	animations.emplace(std::make_pair(animName, Animation()));
}

//----------------------------------------------------------------------------------------------

void CAnimatedSprite::addAnimation(std::string animName, std::vector<IntRect> texRects, std::vector<IntRect> screenRects, unsigned int numFrames, unsigned int speed, bool loop)
{
	animations.emplace((std::make_pair(animName, Animation(texRects, screenRects, 0, numFrames, speed, loop))));
}

//----------------------------------------------------------------------------------------------

void CAnimatedSprite::removeAnimation(std::string animName)
{
	animations.erase(animName);
}

//----------------------------------------------------------------------------------------------

void CAnimatedSprite::setTexture(std::string texName)
{
	m_texName = texName;
	m_tex = resManager.getTexture(m_texName);
	if (!m_tex)
		std::cout << "Couldn't find texture in Resource Manager with name: " + m_texName + ". Can't render sprite with name: " + m_spriteName + "." << std::endl;
	else
		m_sprite.setTexture(*m_tex);
}

//----------------------------------------------------------------------------------------------


/*
inline void CAnimatedSprite::setTextureRect(std::string animName) { //m_sprite.setTextureRect(animations[animName]
																							//.m_texRects[ animations[animName].m_currFrame ]); 
	if(animPlaying) m_sprite.setTextureRect(animPlaying->m_texRects[animPlaying->m_currFrame]);
																	}
inline void CAnimatedSprite::setLocalTextureRect(std::string animName, int frameIndex, IntRect& ir) { animations[animName].m_texRects[frameIndex] = ir; setTextureRect(frameIndex); }

inline void CAnimatedSprite::setPosition(Vector2<float>& pos) { m_sprite.setPosition(pos.x, pos.y); }
inline void CAnimatedSprite::setPosition(float px, float py) { m_sprite.setPosition(px, py); }

inline void CAnimatedSprite::setScale(Vector2<float>& sc) { m_sprite.setScale(sc.x, sc.y); }
inline void CAnimatedSprite::setScale(float sx, float sy) { m_sprite.setScale(sx, sy); }

inline void CAnimatedSprite::setRotation(float angle) { m_sprite.setRotation(angle); }*/
