#pragma once
#include "controllerComponent.h"
#include "vector2D.h"
#include "engine.h"
#include "component.h"

class Waypoint;

class ENGINE_API _TransformControllerComponent : public IControllerComponent
{
public:
	_TransformControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(const Vector2D& position, float rotation, float speed, float rotateRate);
	void Destroy();
	void Update();


protected:
	Vector2D m_position;
	float m_speed = 0.0f;
	float m_rotateRate;
	float m_rotation;
};