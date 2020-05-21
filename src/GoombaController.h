#pragma once
#include "System.h"
#include "EventManager.h"

class GoombaController : public System, public Listener<ColliderEvent>
{
	virtual bool isValid(EntityHandle eh) const override;

	virtual void update(float) override;

	virtual void handle(const ColliderEvent& event) override;

};