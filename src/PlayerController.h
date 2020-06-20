#pragma once

#include "System.h"

class PlayerController : public System
{
	virtual bool isValid(EntityHandle h) const override;

	virtual void update(float dt) override;

	//virtual void init(EntityHandle eh) override;
};