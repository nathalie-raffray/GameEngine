#include "AnimationSystem.h"


AnimationSystem::~AnimationSystem()
{
	for (CAnimatedSprite* sprite : sprites) delete sprite;
}

//----------------------------------------------------------------------------------------------

void AnimationSystem::add(CAnimatedSprite* sc)
{
	sprites.push_back(sc);
	//spriteMap[sc->m_spriteName] = sc;
}

void AnimationSystem::remove(CAnimatedSprite* sc)
{
	sprites.erase(std::remove(sprites.begin(), sprites.end(), sc));
}

//----------------------------------------------------------------------------------------------

void AnimationSystem::playAnimation(std::string name)
{  
	spriteComponent->animPlaying = spriteComponent->getAnimation(name);
	//spriteComponent.paused = false;
	clock.restart();
}

//----------------------------------------------------------------------------------------------

void AnimationSystem::pauseAnimation()
{
	//spriteComponent.paused = true;
	//spriteComponent->animPlaying = nullptr;
}

//----------------------------------------------------------------------------------------------

void AnimationSystem::update()
{
	Animation* anim;
	for (CAnimatedSprite* sprite : sprites)
	{
		if (sprite->isPaused()) continue;
		
		anim = sprite->animPlaying;
		if (anim)
		{
			if (anim->m_numFrames > 1) //else, the "animation" doesn't need to switch frames, it is a static image. 
			{
				if (clock.getElapsedTime().asMilliseconds() >= anim->m_speed)
				{

					int prevFrame = anim->m_currFrame;

					//switch frames
					anim->m_currFrame = (anim->m_currFrame + 1) % anim->m_numFrames;
					unsigned int currFrame = anim->m_currFrame;
					updateTextureRect(sprite);
					updatePositionOffset(sprite);
					updateScale(sprite);

					clock.restart();

					if (!(anim->m_loop) && (prevFrame + 1 >= anim->m_numFrames)) { //if animation doesn't loop and has finished playing last frame
						sprite->animPlaying->m_currFrame = 0;
						sprite->animPlaying = nullptr;
						//sprite->animPlaying->m_currFrame = 0;
						//sprite->
						std::cout << "no loop" << std::endl;
					}

				}
			}
			//updateTextureRect(sprite);
			//updatePositionOffset(sprite);
			//updateScale(sprite);

		}
	}
	
	

}

//----------------------------------------------------------------------------------------------

inline void AnimationSystem::updateTextureRect(CAnimatedSprite* sc)
{
	 (sc->m_sprite).setTextureRect( (sc->animPlaying)->getCurrTexRect());
}

//----------------------------------------------------------------------------------------------

inline void AnimationSystem::updatePositionOffset(CAnimatedSprite* sc)
{
	(sc->m_sprite).setPosition((sc->animPlaying)->getCurrScreenOffset());
}

//----------------------------------------------------------------------------------------------

inline void AnimationSystem::updateScale(CAnimatedSprite* sc)
{
	(sc->m_sprite).setScale((sc->animPlaying)->getCurrScale());
}

//----------------------------------------------------------------------------------------------

inline void AnimationSystem::updateRotation(CAnimatedSprite* sc, float angle)
{
	(sc->m_sprite).setRotation(angle);
}

//----------------------------------------------------------------------------------------------

void AnimationSystem::imguiAnimationEditor()
{

}

//----------------------------------------------------------------------------------------------
