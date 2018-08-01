#include "enemyControllerComponent.h"
#include "vector2D.h"
#include "kinematicComponent.h"
#include "enemy.h"

void EnemyControllerComponent::Create(float speed)
{
	m_speed = speed;
}

void EnemyControllerComponent::Destroy()
{

}

void EnemyControllerComponent::Update()
{
	Vector2D force = Vector2D::zero;

	force = force + Vector2D::up;
	force = force + Vector2D::right;

	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}
}
