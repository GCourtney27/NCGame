#include "shipControllerComponent.h"
#include "inputManager.h"
#include "timer.h"
#include "entity.h"
#include "kinematicComponent.h"
#include "missile.h"
#include "vector2D.h"
#include "audioSystem.h"
#include "scene.h"

void ShipControllerComponent::Create(float speed)
{
	m_speed = speed;

	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("fire", SDL_SCANCODE_SPACE, InputManager::eDevice::KEYBOARD);

	AudioSystem::Instance()->AddSound("fire", "laser.wav");
}

void ShipControllerComponent::Destroy()
{
}

void ShipControllerComponent::Update()
{
	Vector2D force = Vector2D::zero;

	if ((InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::PRESSED) || 
		(InputManager::Instance()->GetActionButton("left") == InputManager::eButtonState::HELD))
	{
		force = force + Vector2D::left;
	}

	if ((InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD))
	{
		force = force + Vector2D::right;
	}

	if ((InputManager::Instance()->GetActionButton("fire") == InputManager::eButtonState::PRESSED))
	{
		std::vector<Entity*> missiles = m_owner->GetScene()->GetEntitiesWithTag("playermissile");

		float dt = Timer::Instance()->DeltaTime();
		m_timer = m_timer - dt;
		if (missiles.size() < 20)
		{
			m_timer = m_fireRate;
			Missile* missle = new Missile(m_owner->GetScene());
			missle->Create("playermissile", m_owner->GetTransform().position, Vector2D::down, 800.0f);
			m_owner->GetScene()->AddEntity(missle);

			AudioSystem::Instance()->PlaySound("fire");
		}
	}


	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();

	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::VELOCITY);
	}

	//TransformComponent* transform = m_owner->GetComponent<TransformComponent>();

	//transform->position = transform->position + (force * m_speed * Timer::Instance()->DeltaTime());

}
