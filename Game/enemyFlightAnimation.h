#pragma once
#include "entity.h"
#include "vector2D.h"

class EnemyFlightAnimation : public Entity
{
public:
	EnemyFlightAnimation(Scene* scene, const ID& id) : Entity(scene, id) {}
	~EnemyFlightAnimation() {}

	void Create(const Vector2D& position);
	void Update();

};