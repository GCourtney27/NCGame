#include "enemyWaypointControllerComponent.h"
#include "kinematicComponent.h"
#include "timer.h"
#include "waypoint.h"
#include "debugDraw.h"
#include "Vector2D.h"

void EnemyWaypointControllerComponent::Create(float speed, std::vector<Vector2D>& points)
{
	m_speed = speed;
	m_timer = Math::GetRandomRange(m_fireRateMin, m_fireRateMax);
	
	for (Vector2D point : points)
	{
		Waypoint* waypoint = m_owner->GetScene()->AddEntity<Waypoint>();
		waypoint->Create(point, Vector2D(10.0f, 10.0f), m_owner);
		m_waypoints.push_back(waypoint);
	}

	m_waypointIndex = 0;
	m_waypoint = m_waypoints[m_waypointIndex];
}

void EnemyWaypointControllerComponent::Destroy()
{
	for (Waypoint* waypoint : m_waypoints)
	{
		waypoint->SetState(Entity::DESTROY);
	}
}

void EnemyWaypointControllerComponent::Update()
{
	if (m_owner->Intersects(m_waypoint))
	{
		SetNextWaypoint();
	}

	DEBUG_DRAW_LINE(m_owner->GetTransform().position, m_waypoint->GetTransform().position, Color::white);

	float dt = Timer::Instance()->DeltaTime();

	Vector2D force = m_waypoint->GetTransform().position - m_owner->GetTransform().position;
	force.Normalize();

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}

	float rotation = Vector2D::GetAngle(force) * Math::RadiansToDegrees + 90.0f;
	m_owner->GetTransform().rotation = Math::Lerp(m_owner->GetTransform().rotation, rotation, 5.0f * dt);


	/*m_timer = m_timer - dt;
	if (m_timer <= 0.0f)
	{
		m_timer = m_fireRate;
		Missile* missle = new Missile(m_owner->GetScene());
		missle->Create("enemymissile", m_owner->GetTransform().position, Vector2D::up, 800.0f);
		m_owner->GetScene()->AddEntity(missle);
	}*/
}

void EnemyWaypointControllerComponent::SetNextWaypoint()
{
	m_waypointIndex++;
	if (m_waypointIndex < m_waypoints.size())
	{
		m_waypoint = m_waypoints[m_waypointIndex];

	}
	else
	{
		m_waypoint->SetState(Entity::DESTROY);
	}
}