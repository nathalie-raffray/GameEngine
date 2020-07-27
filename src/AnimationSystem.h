#pragma once

#include "System.h"

using AnimationId = std::string;

class AnimationSystem : public System
{
	virtual bool isValid(EntityHandle h) const override;

	virtual void update(float dt) override;

};

