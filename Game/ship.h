#pragma once
#include "entity.h"
#include "vector2D.h"

class Ship : public Entity
{
public:
	Ship(Scene* scene, const ID& id) : Entity(scene, id){}
	~Ship() {}

	void Create(const Vector2D& position);
	void Update();

	void OnEvent(const Event& event);

protected:
	float m_lives = 3.0f;
	Vector2D m_lifePosition = Vector2D(100.0f, 550.0f);
};