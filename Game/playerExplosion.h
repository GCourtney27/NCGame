#pragma once
#include "entity.h"
#include "vector2D.h"

class PlayerExplosion : public Entity
{
public:
	PlayerExplosion(Scene* scene, const ID& id) : Entity(scene, id) {}
	~PlayerExplosion() {}

	void Create(const Vector2D& position);
	void Update();

};