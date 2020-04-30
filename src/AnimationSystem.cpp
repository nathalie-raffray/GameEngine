#include "AnimationSystem.h"

/*

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


using SpriteId = std::string;
using TextureId = std::string;
using AnimationId = std::string;

struct AnimationFrame


struct Sprite
{
	struct Rect
	{
		int offsetX, offsetY, width, height;
	};

	TextureId imageId;
	Rect frame;
	//float scale;

	sf::Sprite sprite;
};


struct AnimationFrame
{
	SpriteId spriteId;
	//Vector2 screenOffsets;
	float duration;
};

struct Animation
{
	enum animation_mode
	{
		loop,
		one_time,
		ping_pong
	};

	std::vector<AnimationFrame> frames;
	animation_mode mode;

};


struct AnimationCollection
{
	map<string, unique_ptr<Animation>>  animations;
	//"idle" -> idle animation
}

struct AssetStorage
{
	map<string, unique_ptr<Texture>>    textures;
	map<string, unique_ptr<Sprite>>     sprites;
	//"tree" -> Sprite
	map<string, unique_ptr<AnimationCollection>>  animations;
	//"littlemario" -> AnimationCluster

	void load(string spriteName)
	{
		sprites[spriteName] = loadSprite(spriteName);
	}

	unique_ptr<Sprite> loadSprite(string spriteFilePath)
	{
		// deserialization code
	}

	static Sprite get(SpriteId spriteId);
};


struct Component
{

};

struct Transform : Component
{
	float angle;
	float x, y;
};
*/
/*
void from_json(const json &j, Transform &t)
{
	t.angle = j["angle"];
	t.x = j["x"];
}

void to_json(json &j, const Transform &t)
{
	j["angle"] = t.angle;
}

struct Entity
{
	vector<Component*> comps;
};

#define COMP(Name) if (j["name"] == #Name##Component) { auto c = new NameComponent; *c = j; a = c; }

void from_json(const json &js, Entity &e)
{
	for (auto j : js["components"])
	{
		Component *a = nullptr;
		COMP(Transform);
		COMP(Sprite);
		COMP(...)
		if (a)
		{
			e.comps.emplace_back(a);
		}

	}
}

void serialize()
{
	std::vector<Transform> trans;
	std::ifstream i(filePath);

	json j;
	i >> j;

	trans = j;
}
*/
/*
struct SpriteComponent
{
	// Serializable attribute
	SpriteId spriteId;

	// Transient attributes
};

struct AnimationComponent
{
	// Serializable attribute
	AnimationId currentAnimation = "Idle";
	AnimationGroupId animationGroup;

	// Transient attributes
	int currentFrame = 0;
	float timeAccumulator = 0;
	// or Clock
};


struct RenderingSystem
{
	void update()
	{
	}
};

struct AnimationSystem
{
	std::vector<SpriteComponent> sprites;

	void play(SpriteComponent s, string animationName)
	{
		s.timeAccumulator = 0.0;
	}

	void update(float dt)
	{
		for (auto spriteComp : sprites)
		{
			Sprite sprite = AssetStorage::get(spriteComp.spriteId);

			Animation currentAnim = sprite.animations[spriteComp.currentAnimation];

			auto currentFrame = currentAnim.frames[spriteComp.currentFrame];
			spriteComp.timeAccumulator += dt;

			if (spriteComp.timeAccumulator > currentFrame.timestamp)
			{
				if (currentAnim.loop)
				{
					spriteComp.currentFrame = (spriteComp.currentFrame + 1) % currentAnim.frames.size();
				}
				else
				{
					spriteComp.currentFrame = std::min(spriteComp.currentFrame + 1, currentAnim.frames.size() - 1);
				}
			}
		}
	}
};

*/