#pragma once
#include "entity.h"
#include "vector2D.h"

class Explosion : public Entity
{
public:
	enum eType
	{
		ENEMY,
		PLAYER
	};

public:
	Explosion(Scene* scene, const ID& id) : Entity(scene, id) {}
	~Explosion() {}

	void Create(const ID& explosionType, const Vector2D& position);
	void Update();

};