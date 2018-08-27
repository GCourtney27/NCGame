#include "transformControllerComponent.h"
#include "vector2D.h"
#include "kinematicComponent.h"
#include "enemy.h"
#include "timer.h"

void _TransformControllerComponent::Create(const Vector2D & position, float rotation, float speed, float rotateRate)
{
	m_position = position;
	m_rotation = rotation;
	m_speed = speed;
	m_rotateRate = rotateRate;
}

void _TransformControllerComponent::Destroy()
{

}

void _TransformControllerComponent::Update()
{
	float dt = Timer::Instance()->DeltaTime();

	Vector2D direction = m_position - m_owner->GetTransform().position;
	m_owner->GetTransform().rotation = Math::LerpDegrees(m_owner->GetTransform().rotation, m_rotation, m_rotateRate * dt);

	Vector2D force = direction.Normalized();
	float speedMulti = Math::Clamp01(direction.Length() / 32.0f);
	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * (m_speed * speedMulti), KinematicComponent::VELOCITY);
	}
}
