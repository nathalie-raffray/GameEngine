#pragma once

#include <vector>
#include <memory>
#include <string>

struct AnimationComponent;

using AnimationId = std::string;

class AnimationSystem
{
private:
	std::vector<std::shared_ptr<AnimationComponent>> animatedSprites;

public:
	
	void add(const std::shared_ptr<AnimationComponent>& spA);

	void play(const AnimationId& newAnimation, std::shared_ptr<AnimationComponent>& spA);

	void update();
};

