#pragma once

#include "System.h"

struct EntityCompareByLayer {
	 bool operator()(const EntityHandle& lhs, const EntityHandle& rhs) const {
		return lhs->get<RenderComponent>()->layer < rhs->get<RenderComponent>()->layer;
	}

	/* static bool cmp(const EntityHandle& lhs, const EntityHandle& rhs) {
		 return lhs->get<RenderComponent>()->layer < rhs->get<RenderComponent>()->layer;
	 }*/
};

class RenderingSystem : public System
{
public:

	//RenderingSystem() : System(EntityCompareByLayer{}) {}

	virtual bool isValid(EntityHandle h) const override;

	virtual void update(float dt) override;

	virtual void add(EntityHandle h) override;

};