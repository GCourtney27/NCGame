#pragma once
//engine
#pragma once
#include "controllerComponent.h"
#include "vector2D.h"
#include <vector>
#include "engine.h"

class Waypoint;

class ENGINE_API WaypointControllerComponent : public IControllerComponent
{
public:
	WaypointControllerComponent(Entity* owner) : IControllerComponent(owner) {}

	void Create(float speed, std::vector<Vector2D>& points);
	void Destroy();
	void Update();

	void SetNextWaypoint();

	bool IsComplete() { return m_isComplete; }


protected:
	bool m_isComplete = false;
	float m_speed = 0.0f;

	float m_timer = 0.0f;
	float m_fireRate = 1.0f;
	float m_fireRateMin = 1.0f;
	float m_fireRateMax = 3.0f;

	Waypoint* m_waypoint = nullptr;
	size_t m_waypointIndex = 0;
	std::vector<Waypoint*> m_waypoints;

};