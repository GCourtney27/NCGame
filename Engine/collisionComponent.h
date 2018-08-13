#pragma once
#include "engine.h"
#include "component.h"

class ENGINE_API ICollisionComonent : public Component
{
public:
	ICollisionComonent(Entity* owner) : Component(owner) {}

	virtual bool Intersects(ICollisionComonent* other) = 0;
};