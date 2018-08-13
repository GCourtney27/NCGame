#pragma once

#include "controllerComponent.h"

class ShipControllerComponent : public IControllerComponent
{
public:
	ShipControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(float speed);
	void Destroy();
	void Update();


protected:
	float m_speed;
	float m_timer = 0.0f;
	float m_fireRate = 1.0f;
	float m_fireRateMin = 1.0f;
	float m_fireRateMax = 20.0f;
};