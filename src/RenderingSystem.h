#pragma once

#include "System.h"

class RenderingSystem : System
{
public:

	virtual bool isValid(const EntityHandle& h) override;

	virtual void update(float dt) override;

};