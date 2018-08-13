#include "ship.h"
#include "kinematicComponent.h"
#include "shipControllerComponent.h"
#include "spriteComponent.h"
#include "aabbComponent.h"
#include "renderer.h"
#include "animationComponent.h"

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
		AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
		std::vector<std::string>textureNames = { "ship-explosion01.png", "ship-explosion02.png", "ship-explosion03.png", "ship-explosion04.png" };
		animationComponent->Create(textureNames, 1.0f / 10.0f);

		if (event.sender->GetTag() == "enemy")
		{
			
			// Set explosion here
		
		}

		if (event.sender->GetTag() == "enemymissile")
		{
			SetState(Entity::DESTROY);
			// Set explosion here
		}
	}
}
