#pragma once
#include "collisionComponent.h"
#include "aabb.h"

class ENGINE_API AABBComponent : public ICollisionComonent
{
public:
	AABBComponent(Entity* owner) : ICollisionComonent(owner) {}

	void Create();
	void Destroy();
	void Update();

	virtual bool Intersects(ICollisionComonent* other);

protected:
	AABB m_aabb;
};