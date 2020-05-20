#pragma once

#include <vector>
#include <memory>
#include <string>

#include "System.h"

struct AnimationComponent;

using AnimationId = std::string;

class AnimationSystem : public System
{
private:
	//std::vector<std::shared_ptr<AnimationComponent>> animatedSprites;
	//std::vector<EntityHandle> m_entities;

public:
	
	//virtual void add(const EntityHandle h) override;

	virtual bool isValid(EntityHandle h) const override;

	virtual void update(float dt) override;

};

