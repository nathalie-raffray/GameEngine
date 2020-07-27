#pragma once

#include "System.h"

class AISystem : public System, 
				 public Listener<dynamic_dynamic_collision>,
				 public Listener<triggerstatic_dynamic_collision>
{
	virtual bool isValid(EntityHandle h) const override;

	virtual void update(float dt) override;

	virtual void handle(const dynamic_dynamic_collision& event) override;
	virtual void handle(const triggerstatic_dynamic_collision& event) override;

};

