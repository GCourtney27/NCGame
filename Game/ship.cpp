#include "ship.h"
#include "kinematicComponent.h"
#include "shipControllerComponent.h"
#include "spriteComponent.h"
#include "aabbComponent.h"
#include "renderer.h"
#include "animationComponent.h"
#include "explosion.h"
#include <iostream>

#define LOG(x) std::cout << x << std::endl;

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

	for (size_t i = 0; i < m_lives; i++)
	{
		Entity* entity = GetScene()->AddEntity<Entity>("life");
		if (i > 0)
		{
			m_lifePosition.x += 20;
		}
		entity->GetTransform().position = m_lifePosition;
		SpriteComponent* life = entity->AddComponent<SpriteComponent>();
		life->Create("ship.png", Vector2D(0.5f, 0.5f));
		life->SetDepth(100);
	}
	
}

void Ship::Update()
{
	Entity::Update();

	Vector2D size = Renderer::Instance()->GetSize();
	m_transform.position.x = Math::Clamp(m_transform.position.x, 0.0f, size.x);

	if (m_state == eState::RESPAWN)
	{
		m_lives--;
		// TODO Remove Sprite components from lifes on screen here
		Entity* entity = GetScene()->GetEntityWithID("life");
		entity->SetState(eState::DESTROY);

		SetState(eState::ACTIVE);
		m_transform.position.x = 200.0f;
		std::cout << "Lives Remaining: " << m_lives << std::endl;
		if (m_lives == 0.0f)
		{
			SetState(eState::DESTROY);
			LOG("Game over, ran out of lives");
		}
	}
}

void Ship::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "enemy")
		{
			Explosion* explosion = m_scene->AddEntity<Explosion>();
			const ID& entity = GetTag();
			explosion->Create(entity, m_transform.position);

			SetState(Entity::RESPAWN);
		}

		if (event.sender->GetTag() == "enemymissile")
		{
			Explosion* explosion = m_scene->AddEntity<Explosion>();
			const ID& entity = GetTag();
			explosion->Create(entity, m_transform.position);

			SetState(Entity::RESPAWN);
		}
	}
}
