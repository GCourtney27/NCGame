#include "shipControllerComponent.h"
#include "inputManager.h"
#include "timer.h"
#include "entity.h"
#include "transformComponent.h"
#include "kinematicComponent.h"

void ShipControllerComponent::Create(float speed)
{
	m_speed = speed;

	InputManager::Instance()->AddAction("left", SDL_SCANCODE_LEFT, InputManager::eDevice::KEYBOARD);
	InputManager::Instance()->AddAction("right", SDL_SCANCODE_RIGHT, InputManager::eDevice::KEYBOARD);
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
		//force.x =  -1.0f;
	}

	if ((InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::PRESSED) ||
		(InputManager::Instance()->GetActionButton("right") == InputManager::eButtonState::HELD))
	{
		force = force + Vector2D::right;
		//force.x = 1.0f;
	}


	KinematicComponent* kinematic = m_owner->GetComponent<KinematicComponent>();
	if (kinematic)
	{
		kinematic->ApplyForce(force * m_speed, KinematicComponent::FORCE);
	}

	TransformComponent* transform = m_owner->GetComponent<TransformComponent>();

	transform->position = transform->position + (force * m_speed * Timer::Instance()->DeltaTime());

	
	//getTrasnform component
	//position = transformPosition + force * speed;
}
