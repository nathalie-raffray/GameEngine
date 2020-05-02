#pragma once
#include <memory>
#include <vector>
#include <string>

struct AnimationComponent;
struct SpriteComponent;

using SpriteId = std::string;

class RenderingSystem
{
private:

	std::vector<std::shared_ptr<AnimationComponent>> animatedSprites;
	std::vector<std::shared_ptr<SpriteComponent>> staticSprites;

public:

	void add(const std::shared_ptr<AnimationComponent>& spA);
	
	void update();

	void drawSprite(const SpriteId& id);

};