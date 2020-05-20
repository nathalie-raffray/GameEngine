#pragma once

#include "System.h"

class RenderingSystem : public System
{
public:

	virtual bool isValid(EntityHandle h) const override;

	virtual void update(float dt) override;

};