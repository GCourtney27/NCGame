#include "enemy.h"
#include "kinematicComponent.h"
#include "spriteComponent.h"
#include "enemyControllerComponent.h"
#include "renderer.h"
#include "aabbComponent.h"
#include "audioSystem.h"
#include "eventManager.h"
#include "enemyExplosion.h"
#include "enemyFlightAnimation.h"
#include "animationComponent.h"
#include "enemyWaypointControllerComponent.h"

void Enemy::Create(const Vector2D & position)
{
	SetTag("enemy");
	m_transform.position = position;
	m_transform.scale = Vector2D(2.0f, 2.0f);

	KinematicComponent* kinematic = AddComponent<KinematicComponent>();
	kinematic->Create(500.0f, 0.3f);

	EnemyWaypointControllerComponent* controller = AddComponent<EnemyWaypointControllerComponent>();
	std::vector<Vector2D> points = {Vector2D(100.0f, 100.0f), Vector2D(300.0f, 400.0f), Vector2D(200.0f, 650.0f) };
	controller->Create(200.0f, points);

	SpriteComponent* spriteComponent = AddComponent<SpriteComponent>();
	spriteComponent->Create("enemy01A.png", Vector2D(0.5f, 0.5f));

	AABBComponent* aabbComponent = AddComponent<AABBComponent>();
	aabbComponent->Create(Vector2D(0.7f, 0.9f));

	AnimationComponent* animationComponent = AddComponent<AnimationComponent>();
	std::vector<std::string>textureNames = { "enemy01A.png", "enemy01B.png" };
	animationComponent->Create(textureNames, 1.0f / 10.0f, AnimationComponent::ePlayBack::LOOP);

	//EnemyFlightAnimation* enemyFlightAnimation = m_scene->AddEntity<EnemyFlightAnimation>();
	//enemyFlightAnimation->Create(m_transform.position);
}

void Enemy::Update()
{
	Entity::Update();

	Vector2D size = Renderer::Instance()->GetSize();
	if (m_transform.position.y > size.y)
	{
		float x = Math::GetRandomRange(0.0f, size.y);
		float y = -100.0f;
		m_transform.position = Vector2D(x, y);
	}

	
}

void Enemy::OnEvent(const Event & event)
{
	if (event.eventID == "collision")
	{
		if (event.sender->GetTag() == "playermissile")
		{
 			Event _event;
			_event.eventID = "add_score";
			_event.varient.asInteger = 100;
			_event.varient.type = Varient::INTEGER;

			EventManager::Instance()->SendGameMessage(_event);

			EnemyExplosion* explosion = m_scene->AddEntity<EnemyExplosion>();
			explosion->Create(m_transform.position);

			SetState(Entity::DESTROY);
		}

		if (event.sender->GetTag() == "player")
		{
			SetState(Entity::DESTROY);
		}
	}
}

