#pragma once
#include "System.h"
#include "EventManager.h"

class RigidbodyPhysics : public System, 
						 public Listener<static_dynamic_collision>
{
	bool isValid(EntityHandle eh) const override;

	void init(EntityHandle eh) override;

	void update(float dt) override;

	virtual void handle(const static_dynamic_collision& event) override;
};