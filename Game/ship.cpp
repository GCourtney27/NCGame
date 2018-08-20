#include "ship.h"
#include "kinematicComponent.h"
#include "shipControllerComponent.h"
#include "spriteComponent.h"
#include "aabbComponent.h"
#include "renderer.h"
#include "animationComponent.h"
#include "playerExplosion.h"

void Ship::Create(const Vector2D & position)
{
	SetTag("player");
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	ShipControllerComponent* ship = AddComponent<ShipControllerComponent>();
	ship->Create(500.0f);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("ship.png", Vector2D(0.5f, 0.5f));

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create();

	
	
}

void Ship::Update()
{
	Entity::Update();

	Vector2D size = Renderer::Instance()->GetSize();
	m_transform.position.x = Math::Clamp(m_transform.position.x, 0.0f, size.x);
}

void Ship::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "enemy")
		{
			PlayerExplosion* explosion = m_scene->AddEntity<PlayerExplosion>();
			explosion->Create(m_transform.position);

			SetState(Entity::DESTROY);
		}

		if (event.sender->GetTag() == "enemymissile")
		{
			PlayerExplosion* explosion = m_scene->AddEntity<PlayerExplosion>();
			explosion->Create(m_transform.position);

			SetState(Entity::DESTROY);
		}
	}
}
