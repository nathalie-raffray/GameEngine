#pragma once

#include <vector>
#include <memory>
#include <string>

#include "System.h"

struct AnimationComponent;

using AnimationId = std::string;

class AnimationSystem : public System
{

	virtual bool isValid(EntityHandle h) const override;

	virtual void update(float dt) override;

};

