#pragma once
#include "System.h"

class Camera : public System
{
	bool isValid(EntityHandle eh) const override;

	void init(EntityHandle eh) override;

	void update(float) override;

private:
	//i think the data below should be in a camera component or some shit. systems shouldn't have data?
	EntityHandle player; //= INVALID
	EntityHandle camera;
};
